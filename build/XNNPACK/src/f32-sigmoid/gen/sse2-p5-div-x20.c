// Auto-generated file. Do not edit!
//   Template: src/f32-sigmoid/sse-p5-div.c.in
//   Generator: tools/xngen
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <emmintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/vunary.h>


void xnn_f32_sigmoid_ukernel__sse2_p5_div_x20(
    size_t n,
    const float* x,
    float* y,
    const void* params) XNN_DISABLE_TSAN
{
  assert(n % sizeof(float) == 0);

  const __m128 vsign_mask = _mm_set1_ps(-0.0f);
  const __m128 vmagic_bias = _mm_set1_ps(0x1.8000FEp23f);
  const __m128 vlog2e = _mm_set1_ps(0x1.715476p0f);
  const __m128 vminus_ln2_hi = _mm_set1_ps(-0x1.62E400p-1f);
  const __m128 vminus_ln2_lo = _mm_set1_ps(-0x1.7F7D1Cp-20f);
  const __m128 vc5 = _mm_set1_ps(0x1.0F9F9Cp-7f);
  const __m128 vc4 = _mm_set1_ps(0x1.573A1Ap-5f);
  const __m128 vc3 = _mm_set1_ps(0x1.555A80p-3f);
  const __m128 vc2 = _mm_set1_ps(0x1.FFFDC6p-2f);
  const __m128 vc1 = _mm_set1_ps(0x1.FFFFF6p-1f);
  const __m128 vone = _mm_set1_ps(1.0f);
  const __m128 vdenorm_cutoff = _mm_set1_ps(-0x1.5D589Ep+6f);

  for (; n >= 20 * sizeof(float); n -= 20 * sizeof(float)) {
    const __m128 vx0123 = _mm_loadu_ps(x);
    const __m128 vx4567 = _mm_loadu_ps(x + 4);
    const __m128 vx89AB = _mm_loadu_ps(x + 8);
    const __m128 vxCDEF = _mm_loadu_ps(x + 12);
    const __m128 vxGHIJ = _mm_loadu_ps(x + 16);

    const __m128 vz0123 = _mm_or_ps(vx0123, vsign_mask);
    const __m128 vz4567 = _mm_or_ps(vx4567, vsign_mask);
    const __m128 vz89AB = _mm_or_ps(vx89AB, vsign_mask);
    const __m128 vzCDEF = _mm_or_ps(vxCDEF, vsign_mask);
    const __m128 vzGHIJ = _mm_or_ps(vxGHIJ, vsign_mask);

    __m128 vn0123 = _mm_add_ps(_mm_mul_ps(vz0123, vlog2e), vmagic_bias);
    __m128 vn4567 = _mm_add_ps(_mm_mul_ps(vz4567, vlog2e), vmagic_bias);
    __m128 vn89AB = _mm_add_ps(_mm_mul_ps(vz89AB, vlog2e), vmagic_bias);
    __m128 vnCDEF = _mm_add_ps(_mm_mul_ps(vzCDEF, vlog2e), vmagic_bias);
    __m128 vnGHIJ = _mm_add_ps(_mm_mul_ps(vzGHIJ, vlog2e), vmagic_bias);

    const __m128 vs0123 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn0123), 23));
    const __m128 vs4567 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn4567), 23));
    const __m128 vs89AB = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn89AB), 23));
    const __m128 vsCDEF = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vnCDEF), 23));
    const __m128 vsGHIJ = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vnGHIJ), 23));

    vn0123 = _mm_sub_ps(vn0123, vmagic_bias);
    vn4567 = _mm_sub_ps(vn4567, vmagic_bias);
    vn89AB = _mm_sub_ps(vn89AB, vmagic_bias);
    vnCDEF = _mm_sub_ps(vnCDEF, vmagic_bias);
    vnGHIJ = _mm_sub_ps(vnGHIJ, vmagic_bias);

    __m128 vt0123 = _mm_add_ps(_mm_mul_ps(vn0123, vminus_ln2_hi), vz0123);
    __m128 vt4567 = _mm_add_ps(_mm_mul_ps(vn4567, vminus_ln2_hi), vz4567);
    __m128 vt89AB = _mm_add_ps(_mm_mul_ps(vn89AB, vminus_ln2_hi), vz89AB);
    __m128 vtCDEF = _mm_add_ps(_mm_mul_ps(vnCDEF, vminus_ln2_hi), vzCDEF);
    __m128 vtGHIJ = _mm_add_ps(_mm_mul_ps(vnGHIJ, vminus_ln2_hi), vzGHIJ);

    vt0123 = _mm_add_ps(_mm_mul_ps(vn0123, vminus_ln2_lo), vt0123);
    vt4567 = _mm_add_ps(_mm_mul_ps(vn4567, vminus_ln2_lo), vt4567);
    vt89AB = _mm_add_ps(_mm_mul_ps(vn89AB, vminus_ln2_lo), vt89AB);
    vtCDEF = _mm_add_ps(_mm_mul_ps(vnCDEF, vminus_ln2_lo), vtCDEF);
    vtGHIJ = _mm_add_ps(_mm_mul_ps(vnGHIJ, vminus_ln2_lo), vtGHIJ);

    __m128 vp0123 = _mm_add_ps(_mm_mul_ps(vc5, vt0123), vc4);
    __m128 vp4567 = _mm_add_ps(_mm_mul_ps(vc5, vt4567), vc4);
    __m128 vp89AB = _mm_add_ps(_mm_mul_ps(vc5, vt89AB), vc4);
    __m128 vpCDEF = _mm_add_ps(_mm_mul_ps(vc5, vtCDEF), vc4);
    __m128 vpGHIJ = _mm_add_ps(_mm_mul_ps(vc5, vtGHIJ), vc4);

    vp0123 = _mm_add_ps(_mm_mul_ps(vp0123, vt0123), vc3);
    vp4567 = _mm_add_ps(_mm_mul_ps(vp4567, vt4567), vc3);
    vp89AB = _mm_add_ps(_mm_mul_ps(vp89AB, vt89AB), vc3);
    vpCDEF = _mm_add_ps(_mm_mul_ps(vpCDEF, vtCDEF), vc3);
    vpGHIJ = _mm_add_ps(_mm_mul_ps(vpGHIJ, vtGHIJ), vc3);

    vp0123 = _mm_add_ps(_mm_mul_ps(vp0123, vt0123), vc2);
    vp4567 = _mm_add_ps(_mm_mul_ps(vp4567, vt4567), vc2);
    vp89AB = _mm_add_ps(_mm_mul_ps(vp89AB, vt89AB), vc2);
    vpCDEF = _mm_add_ps(_mm_mul_ps(vpCDEF, vtCDEF), vc2);
    vpGHIJ = _mm_add_ps(_mm_mul_ps(vpGHIJ, vtGHIJ), vc2);

    vp0123 = _mm_add_ps(_mm_mul_ps(vp0123, vt0123), vc1);
    vp4567 = _mm_add_ps(_mm_mul_ps(vp4567, vt4567), vc1);
    vp89AB = _mm_add_ps(_mm_mul_ps(vp89AB, vt89AB), vc1);
    vpCDEF = _mm_add_ps(_mm_mul_ps(vpCDEF, vtCDEF), vc1);
    vpGHIJ = _mm_add_ps(_mm_mul_ps(vpGHIJ, vtGHIJ), vc1);

    vt0123 = _mm_mul_ps(vt0123, vs0123);
    vt4567 = _mm_mul_ps(vt4567, vs4567);
    vt89AB = _mm_mul_ps(vt89AB, vs89AB);
    vtCDEF = _mm_mul_ps(vtCDEF, vsCDEF);
    vtGHIJ = _mm_mul_ps(vtGHIJ, vsGHIJ);

    __m128 ve0123 = _mm_add_ps(_mm_mul_ps(vt0123, vp0123), vs0123);
    __m128 ve4567 = _mm_add_ps(_mm_mul_ps(vt4567, vp4567), vs4567);
    __m128 ve89AB = _mm_add_ps(_mm_mul_ps(vt89AB, vp89AB), vs89AB);
    __m128 veCDEF = _mm_add_ps(_mm_mul_ps(vtCDEF, vpCDEF), vsCDEF);
    __m128 veGHIJ = _mm_add_ps(_mm_mul_ps(vtGHIJ, vpGHIJ), vsGHIJ);

    __m128 vd0123 = _mm_add_ps(ve0123, vone);
    __m128 vd4567 = _mm_add_ps(ve4567, vone);
    __m128 vd89AB = _mm_add_ps(ve89AB, vone);
    __m128 vdCDEF = _mm_add_ps(veCDEF, vone);
    __m128 vdGHIJ = _mm_add_ps(veGHIJ, vone);

    __m128 vf0123 = _mm_div_ps(ve0123, vd0123);
    __m128 vf4567 = _mm_div_ps(ve4567, vd4567);
    __m128 vf89AB = _mm_div_ps(ve89AB, vd89AB);
    __m128 vfCDEF = _mm_div_ps(veCDEF, vdCDEF);
    __m128 vfGHIJ = _mm_div_ps(veGHIJ, vdGHIJ);

    vf0123 = _mm_andnot_ps(_mm_cmplt_ps(vz0123, vdenorm_cutoff), vf0123);
    vf4567 = _mm_andnot_ps(_mm_cmplt_ps(vz4567, vdenorm_cutoff), vf4567);
    vf89AB = _mm_andnot_ps(_mm_cmplt_ps(vz89AB, vdenorm_cutoff), vf89AB);
    vfCDEF = _mm_andnot_ps(_mm_cmplt_ps(vzCDEF, vdenorm_cutoff), vfCDEF);
    vfGHIJ = _mm_andnot_ps(_mm_cmplt_ps(vzGHIJ, vdenorm_cutoff), vfGHIJ);

    const __m128 vm0123 = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vx0123)));
    const __m128 vm4567 = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vx4567)));
    const __m128 vm89AB = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vx89AB)));
    const __m128 vmCDEF = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vxCDEF)));
    const __m128 vmGHIJ = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vxGHIJ)));

    vf0123 = _mm_or_ps(_mm_and_ps(vf0123, vm0123), _mm_andnot_ps(vm0123, _mm_sub_ps(vone, vf0123)));
    vf4567 = _mm_or_ps(_mm_and_ps(vf4567, vm4567), _mm_andnot_ps(vm4567, _mm_sub_ps(vone, vf4567)));
    vf89AB = _mm_or_ps(_mm_and_ps(vf89AB, vm89AB), _mm_andnot_ps(vm89AB, _mm_sub_ps(vone, vf89AB)));
    vfCDEF = _mm_or_ps(_mm_and_ps(vfCDEF, vmCDEF), _mm_andnot_ps(vmCDEF, _mm_sub_ps(vone, vfCDEF)));
    vfGHIJ = _mm_or_ps(_mm_and_ps(vfGHIJ, vmGHIJ), _mm_andnot_ps(vmGHIJ, _mm_sub_ps(vone, vfGHIJ)));

    _mm_storeu_ps(y, vf0123);
    _mm_storeu_ps(y + 4, vf4567);
    _mm_storeu_ps(y + 8, vf89AB);
    _mm_storeu_ps(y + 12, vfCDEF);
    _mm_storeu_ps(y + 16, vfGHIJ);

    x += 20;
    y += 20;
  }
  for (; n >= 4 * sizeof(float); n -= 4 * sizeof(float)) {
    const __m128 vx = _mm_loadu_ps(x);

    const __m128 vz = _mm_or_ps(vx, vsign_mask);

    __m128 vn = _mm_add_ps(_mm_mul_ps(vz, vlog2e), vmagic_bias);
    const __m128 vs = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn), 23));
    vn = _mm_sub_ps(vn, vmagic_bias);

    __m128 vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_hi), vz);
    vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_lo), vt);

    __m128 vp = _mm_add_ps(_mm_mul_ps(vc5, vt), vc4);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc3);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc2);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc1);

    vt = _mm_mul_ps(vt, vs);
    __m128 ve = _mm_add_ps(_mm_mul_ps(vt, vp), vs);

    __m128 vd = _mm_add_ps(ve, vone);
    __m128 vf = _mm_div_ps(ve, vd);

    vf = _mm_andnot_ps(_mm_cmplt_ps(vz, vdenorm_cutoff), vf);
    const __m128 vm = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vx)));
    vf = _mm_or_ps(_mm_and_ps(vf, vm), _mm_andnot_ps(vm, _mm_sub_ps(vone, vf)));

    _mm_storeu_ps(y, vf);

    x += 4;
    y += 4;
  }
  if XNN_UNLIKELY(n != 0) {
    const __m128 vx = _mm_loadu_ps(x);

    const __m128 vz = _mm_or_ps(vx, vsign_mask);

    __m128 vn = _mm_add_ps(_mm_mul_ps(vz, vlog2e), vmagic_bias);
    const __m128 vs = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn), 23));
    vn = _mm_sub_ps(vn, vmagic_bias);

    __m128 vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_hi), vz);
    vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_lo), vt);

    __m128 vp = _mm_add_ps(_mm_mul_ps(vc5, vt), vc4);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc3);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc2);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc1);

    vt = _mm_mul_ps(vt, vs);
    __m128 ve = _mm_add_ps(_mm_mul_ps(vt, vp), vs);

    __m128 vd = _mm_add_ps(ve, vone);
    __m128 vf = _mm_div_ps(ve, vd);

    vf = _mm_andnot_ps(_mm_cmplt_ps(vz, vdenorm_cutoff), vf);
    const __m128 vm = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vx)));
    vf = _mm_or_ps(_mm_and_ps(vf, vm), _mm_andnot_ps(vm, _mm_sub_ps(vone, vf)));

    if (n & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) y, vf);
      vf = _mm_movehl_ps(vf, vf);
      y += 2;
    }
    if (n & (1 * sizeof(float))) {
      _mm_store_ss(y, vf);
    }
  }
}
