#pragma once
#include <memory>
#include "Types.h"
#include <Constants.h>
#include <vector>


class Material;

struct intersectionRec
{
	const float tmin;
	const Point3 hit_point;
	const Vector3 normal;
	std::shared_ptr<Material> material;
	const float u = 0;
	const float v = 0;
};


struct intersectionRecSoA {
	mask_type intersects = mask_type(false);
	batch_type tmin = batch_type(Constants::MAX_FLOAT);
	Point3_SoA hit_point;
	Vector3_SoA normal;
	batch_type u = batch_type(Constants::MAX_FLOAT); 
	batch_type v = batch_type(Constants::MAX_FLOAT);;

	std::array<std::shared_ptr<Material>, SIMD_WIDTH> materials;

	//intersectionRecSoA() : intersects(false) {
	//	// Other initialization logic can go here
	//}
	void blend(const intersectionRecSoA& other, const mask_type& mask) {
		tmin = xs::select(mask, other.tmin, tmin);

		// Blend hit points
		hit_point.x = xs::select(mask, other.hit_point.x, hit_point.x);
		hit_point.y = xs::select(mask, other.hit_point.y, hit_point.y);
		hit_point.z = xs::select(mask, other.hit_point.z, hit_point.z);

		// Blend normals
		normal.x = xs::select(mask, other.normal.x, normal.x);
		normal.y = xs::select(mask, other.normal.y, normal.y);
		normal.z = xs::select(mask, other.normal.z, normal.z);

		// Blend texture coordinates
		u = xs::select(mask, other.u, u);
		v = xs::select(mask, other.v, v);

		// Blend intersection mask itself
		intersects = intersects | mask;

		// Blend materials per lane
		for (size_t i = 0; i < SIMD_WIDTH; ++i) {
			if (mask.get(i)) {
				materials[i] = other.materials[i];
			}
		}
	}

	void set_from_scalar(const intersectionRec& rec, size_t i) {
		// Criamos um array na stack que é garantidamente alinhado para as operações SIMD.
		alignas(xs::default_arch::alignment()) float arr[SIMD_WIDTH];

		// Padrão "Store-Modify-Load" para cada membro do tipo 'batch_type'

		// tmin
		xs::store_aligned(arr, tmin);      // 1. Store: Copia o registrador SIMD para o array.
		arr[i] = rec.tmin;                 // 2. Modify: Altera o valor escalar no array.
		tmin = xs::load_aligned(arr);      // 3. Load: Carrega o array modificado de volta para o registrador.

		// u, v
		xs::store_aligned(arr, u); arr[i] = rec.u; u = xs::load_aligned(arr);
		xs::store_aligned(arr, v); arr[i] = rec.v; v = xs::load_aligned(arr);

		// hit_point
		xs::store_aligned(arr, hit_point.x); arr[i] = rec.hit_point.x; hit_point.x = xs::load_aligned(arr);
		xs::store_aligned(arr, hit_point.y); arr[i] = rec.hit_point.y; hit_point.y = xs::load_aligned(arr);
		xs::store_aligned(arr, hit_point.z); arr[i] = rec.hit_point.z; hit_point.z = xs::load_aligned(arr);

		// normal
		xs::store_aligned(arr, normal.x); arr[i] = rec.normal.x; normal.x = xs::load_aligned(arr);
		xs::store_aligned(arr, normal.y); arr[i] = rec.normal.y; normal.y = xs::load_aligned(arr);
		xs::store_aligned(arr, normal.z); arr[i] = rec.normal.z; normal.z = xs::load_aligned(arr);

		intersects = intersects | mask_type::from_mask(1ULL << i);



		// Dados não-vetorizáveis são atualizados diretamente.
		materials[i] = rec.material;
	}

};



inline std::vector<std::pair<size_t, intersectionRec>> explode(const intersectionRecSoA& soa) {
	// Array declarations remain the same...
	alignas(xs::default_arch::alignment()) float tmin_arr[SIMD_WIDTH];
	alignas(xs::default_arch::alignment()) float x_arr[SIMD_WIDTH];
	alignas(xs::default_arch::alignment()) float y_arr[SIMD_WIDTH];
	alignas(xs::default_arch::alignment()) float z_arr[SIMD_WIDTH];
	alignas(xs::default_arch::alignment()) float nx_arr[SIMD_WIDTH];
	alignas(xs::default_arch::alignment()) float ny_arr[SIMD_WIDTH];
	alignas(xs::default_arch::alignment()) float nz_arr[SIMD_WIDTH];
	alignas(xs::default_arch::alignment()) float u_arr[SIMD_WIDTH];
	alignas(xs::default_arch::alignment()) float v_arr[SIMD_WIDTH];

	// Bulk extraction remains the same...
	soa.tmin.store_aligned(tmin_arr);
	soa.hit_point.x.store_aligned(x_arr);
	soa.hit_point.y.store_aligned(y_arr);
	soa.hit_point.z.store_aligned(z_arr);
	soa.normal.x.store_aligned(nx_arr);
	soa.normal.y.store_aligned(ny_arr);
	soa.normal.z.store_aligned(nz_arr);
	soa.u.store_aligned(u_arr);
	soa.v.store_aligned(v_arr);

	std::vector<std::pair<size_t, intersectionRec>> out;
	out.reserve(SIMD_WIDTH);
	for (size_t i = 0; i < SIMD_WIDTH; ++i) {
		bool mask_value = soa.intersects.get(i);

		if (!mask_value) continue;

		const auto rec = intersectionRec{
			tmin_arr[i],
			{ x_arr[i],  y_arr[i],  z_arr[i] },
			{ nx_arr[i], ny_arr[i], nz_arr[i] },
			soa.materials[i],
			u_arr[i],
			v_arr[i],
		};

		// MODIFICAÇÃO 2: Adicionamos o índice 'i' junto com o registro
		out.push_back({ i, rec });
	}
	return out;
}
