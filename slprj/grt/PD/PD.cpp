/*
 * Code generation for system model 'PD'
 *
 * Model                      : PD
 * Model version              : 1.68
 * Simulink Coder version : 26.1 (R2026a) 20-Nov-2025
 * C++ source code generated on : Thu Oct 22 16:06:09 2026
 *
 * Note that the functions contained in this file are part of a Simulink
 * model, and are not self-contained algorithms.
 */

#include "PD.h"
#include "rtwtypes.h"
#include <cmath>
#include <emmintrin.h>
#include <cstring>
#include "mldivide_0QKHZcd4.h"
#include "PD_types.h"
#include "PD_private.h"

/* Output and update for referenced model: 'PD' */
void PD::step(const real_T rtu_InBus_qd[8], const real_T rtu_InBus_dqd[8], const
              real_T rtu_InBus_ddqd[8], const real_T rtu_InBus1_Positions[8],
              const real_T rtu_InBus1_Velocities[8], real_T rty_Output2[8])
{
  __m128d tmp_hw;
  __m128d tmp_hx;
  __m128d tmp_hy;
  __m128d tmp_i3;
  real_T tmp_hr[64];
  real_T tmp_hu[64];
  real_T x[64];
  real_T tmp_hs[8];
  real_T tmp_ht[8];
  real_T tmp_hv[2];
  real_T D14;
  real_T D14_tmp;
  real_T D14_tmp_0;
  real_T D14_tmp_1;
  real_T D14_tmp_2;
  real_T D14_tmp_3;
  real_T D14_tmp_4;
  real_T D14_tmp_5;
  real_T D14_tmp_tmp;
  real_T D15;
  real_T D15_tmp;
  real_T D15_tmp_0;
  real_T D15_tmp_1;
  real_T D15_tmp_2;
  real_T D15_tmp_tmp;
  real_T D15_tmp_tmp_0;
  real_T D16;
  real_T D17;
  real_T D17_tmp;
  real_T D17_tmp_0;
  real_T D18;
  real_T D24;
  real_T D24_tmp;
  real_T D24_tmp_0;
  real_T D25;
  real_T D27;
  real_T D28;
  real_T D34;
  real_T D34_tmp;
  real_T D34_tmp_0;
  real_T D34_tmp_1;
  real_T D35;
  real_T D37;
  real_T D37_tmp;
  real_T D38;
  real_T D45;
  real_T D45_tmp;
  real_T D45_tmp_0;
  real_T D45_tmp_1;
  real_T D46_tmp;
  real_T D46_tmp_0;
  real_T D46_tmp_1;
  real_T D46_tmp_10;
  real_T D46_tmp_11;
  real_T D46_tmp_12;
  real_T D46_tmp_2;
  real_T D46_tmp_3;
  real_T D46_tmp_4;
  real_T D46_tmp_5;
  real_T D46_tmp_6;
  real_T D46_tmp_7;
  real_T D46_tmp_8;
  real_T D46_tmp_9;
  real_T D46_tmp_a;
  real_T D46_tmp_b;
  real_T D46_tmp_c;
  real_T D46_tmp_d;
  real_T D46_tmp_e;
  real_T D46_tmp_f;
  real_T D46_tmp_g;
  real_T D46_tmp_h;
  real_T D46_tmp_i;
  real_T D46_tmp_j;
  real_T D46_tmp_k;
  real_T D46_tmp_l;
  real_T D46_tmp_m;
  real_T D46_tmp_n;
  real_T D46_tmp_o;
  real_T D46_tmp_p;
  real_T D46_tmp_q;
  real_T D46_tmp_r;
  real_T D46_tmp_s;
  real_T D46_tmp_t;
  real_T D46_tmp_tmp;
  real_T D46_tmp_tmp_0;
  real_T D46_tmp_tmp_1;
  real_T D46_tmp_tmp_2;
  real_T D46_tmp_tmp_3;
  real_T D46_tmp_tmp_4;
  real_T D46_tmp_tmp_5;
  real_T D46_tmp_tmp_6;
  real_T D46_tmp_tmp_7;
  real_T D46_tmp_tmp_8;
  real_T D46_tmp_tmp_9;
  real_T D46_tmp_tmp_a;
  real_T D46_tmp_tmp_b;
  real_T D46_tmp_tmp_c;
  real_T D46_tmp_tmp_d;
  real_T D46_tmp_tmp_e;
  real_T D46_tmp_tmp_f;
  real_T D46_tmp_u;
  real_T D46_tmp_v;
  real_T D46_tmp_w;
  real_T D46_tmp_x;
  real_T D46_tmp_y;
  real_T D46_tmp_z;
  real_T D47;
  real_T D47_tmp;
  real_T D47_tmp_0;
  real_T D47_tmp_1;
  real_T D47_tmp_2;
  real_T D47_tmp_3;
  real_T D47_tmp_4;
  real_T D47_tmp_5;
  real_T D47_tmp_tmp_tmp;
  real_T D48;
  real_T D48_tmp;
  real_T D48_tmp_0;
  real_T D56;
  real_T D56_tmp;
  real_T D56_tmp_0;
  real_T D56_tmp_1;
  real_T D56_tmp_2;
  real_T D56_tmp_3;
  real_T D56_tmp_4;
  real_T D56_tmp_5;
  real_T D56_tmp_6;
  real_T D56_tmp_7;
  real_T D56_tmp_8;
  real_T D56_tmp_9;
  real_T D56_tmp_a;
  real_T D56_tmp_b;
  real_T D56_tmp_c;
  real_T D56_tmp_d;
  real_T D56_tmp_e;
  real_T D56_tmp_f;
  real_T D56_tmp_g;
  real_T D56_tmp_h;
  real_T D56_tmp_i;
  real_T D56_tmp_j;
  real_T D56_tmp_k;
  real_T D56_tmp_l;
  real_T D56_tmp_m;
  real_T D56_tmp_n;
  real_T D56_tmp_o;
  real_T D56_tmp_p;
  real_T D56_tmp_q;
  real_T D56_tmp_r;
  real_T D56_tmp_s;
  real_T D56_tmp_tmp;
  real_T D56_tmp_tmp_0;
  real_T D56_tmp_tmp_1;
  real_T D56_tmp_tmp_2;
  real_T D56_tmp_tmp_3;
  real_T D56_tmp_tmp_4;
  real_T D56_tmp_tmp_5;
  real_T D56_tmp_tmp_6;
  real_T D56_tmp_tmp_7;
  real_T D56_tmp_tmp_8;
  real_T D56_tmp_tmp_9;
  real_T D56_tmp_tmp_a;
  real_T D56_tmp_tmp_b;
  real_T D56_tmp_tmp_c;
  real_T D56_tmp_tmp_d;
  real_T D56_tmp_tmp_e;
  real_T D56_tmp_tmp_f;
  real_T D56_tmp_tmp_g;
  real_T D56_tmp_tmp_h;
  real_T D56_tmp_tmp_i;
  real_T D56_tmp_tmp_j;
  real_T D56_tmp_tmp_k;
  real_T D56_tmp_tmp_l;
  real_T D56_tmp_tmp_m;
  real_T D56_tmp_tmp_n;
  real_T D56_tmp_tmp_o;
  real_T D56_tmp_tmp_p;
  real_T D56_tmp_tmp_q;
  real_T D56_tmp_tmp_r;
  real_T D56_tmp_tmp_tmp;
  real_T D57;
  real_T D67_tmp;
  real_T D67_tmp_0;
  real_T a;
  real_T ab_a;
  real_T c_a;
  real_T d_a;
  real_T e_a;
  real_T f_a;
  real_T g_a;
  real_T ginv_tmp;
  real_T ginv_tmp_0;
  real_T ginv_tmp_1;
  real_T ginv_tmp_2;
  real_T ginv_tmp_3;
  real_T ginv_tmp_4;
  real_T ginv_tmp_5;
  real_T ginv_tmp_6;
  real_T ginv_tmp_7;
  real_T ginv_tmp_8;
  real_T ginv_tmp_9;
  real_T ginv_tmp_a;
  real_T ginv_tmp_b;
  real_T ginv_tmp_c;
  real_T ginv_tmp_d;
  real_T ginv_tmp_e;
  real_T ginv_tmp_f;
  real_T ginv_tmp_tmp;
  real_T ginv_tmp_tmp_0;
  real_T ginv_tmp_tmp_1;
  real_T ginv_tmp_tmp_2;
  real_T ginv_tmp_tmp_3;
  real_T h_a;
  real_T i_a;
  real_T j_a;
  real_T k_a;
  real_T l_a;
  real_T m_a;
  real_T n_a;
  real_T o_a;
  real_T p_a;
  real_T q_a;
  real_T r_a;
  real_T s;
  real_T s_a;
  real_T smax;
  real_T smax_tmp;
  real_T t_a;
  real_T tmp;
  real_T tmp_0;
  real_T tmp_1;
  real_T tmp_10;
  real_T tmp_11;
  real_T tmp_12;
  real_T tmp_13;
  real_T tmp_14;
  real_T tmp_15;
  real_T tmp_16;
  real_T tmp_17;
  real_T tmp_18;
  real_T tmp_19;
  real_T tmp_1a;
  real_T tmp_1b;
  real_T tmp_1c;
  real_T tmp_1d;
  real_T tmp_1e;
  real_T tmp_1f;
  real_T tmp_1g;
  real_T tmp_1h;
  real_T tmp_1i;
  real_T tmp_1j;
  real_T tmp_1k;
  real_T tmp_1l;
  real_T tmp_1m;
  real_T tmp_1n;
  real_T tmp_1o;
  real_T tmp_1p;
  real_T tmp_1q;
  real_T tmp_1r;
  real_T tmp_1s;
  real_T tmp_1t;
  real_T tmp_1u;
  real_T tmp_1v;
  real_T tmp_1w;
  real_T tmp_1x;
  real_T tmp_1y;
  real_T tmp_1z;
  real_T tmp_2;
  real_T tmp_20;
  real_T tmp_21;
  real_T tmp_22;
  real_T tmp_23;
  real_T tmp_24;
  real_T tmp_25;
  real_T tmp_26;
  real_T tmp_27;
  real_T tmp_28;
  real_T tmp_29;
  real_T tmp_2a;
  real_T tmp_2b;
  real_T tmp_2c;
  real_T tmp_2d;
  real_T tmp_2e;
  real_T tmp_2f;
  real_T tmp_2g;
  real_T tmp_2h;
  real_T tmp_2i;
  real_T tmp_2j;
  real_T tmp_2k;
  real_T tmp_2l;
  real_T tmp_2m;
  real_T tmp_2n;
  real_T tmp_2o;
  real_T tmp_2p;
  real_T tmp_2q;
  real_T tmp_2r;
  real_T tmp_2s;
  real_T tmp_2t;
  real_T tmp_2u;
  real_T tmp_2v;
  real_T tmp_2w;
  real_T tmp_2x;
  real_T tmp_2y;
  real_T tmp_2z;
  real_T tmp_3;
  real_T tmp_30;
  real_T tmp_31;
  real_T tmp_32;
  real_T tmp_33;
  real_T tmp_34;
  real_T tmp_35;
  real_T tmp_36;
  real_T tmp_37;
  real_T tmp_38;
  real_T tmp_39;
  real_T tmp_3a;
  real_T tmp_3b;
  real_T tmp_3c;
  real_T tmp_3d;
  real_T tmp_3e;
  real_T tmp_3f;
  real_T tmp_3g;
  real_T tmp_3h;
  real_T tmp_3i;
  real_T tmp_3j;
  real_T tmp_3k;
  real_T tmp_3l;
  real_T tmp_3m;
  real_T tmp_3n;
  real_T tmp_3o;
  real_T tmp_3p;
  real_T tmp_3q;
  real_T tmp_3r;
  real_T tmp_3s;
  real_T tmp_3t;
  real_T tmp_3u;
  real_T tmp_3v;
  real_T tmp_3w;
  real_T tmp_3x;
  real_T tmp_3y;
  real_T tmp_3z;
  real_T tmp_4;
  real_T tmp_40;
  real_T tmp_41;
  real_T tmp_42;
  real_T tmp_43;
  real_T tmp_44;
  real_T tmp_45;
  real_T tmp_46;
  real_T tmp_47;
  real_T tmp_48;
  real_T tmp_49;
  real_T tmp_4a;
  real_T tmp_4b;
  real_T tmp_4c;
  real_T tmp_4d;
  real_T tmp_4e;
  real_T tmp_4f;
  real_T tmp_4g;
  real_T tmp_4h;
  real_T tmp_4i;
  real_T tmp_4j;
  real_T tmp_4k;
  real_T tmp_4l;
  real_T tmp_4m;
  real_T tmp_4n;
  real_T tmp_4o;
  real_T tmp_4p;
  real_T tmp_4q;
  real_T tmp_4r;
  real_T tmp_4s;
  real_T tmp_4t;
  real_T tmp_4u;
  real_T tmp_4v;
  real_T tmp_4w;
  real_T tmp_4x;
  real_T tmp_4y;
  real_T tmp_4z;
  real_T tmp_5;
  real_T tmp_50;
  real_T tmp_51;
  real_T tmp_52;
  real_T tmp_53;
  real_T tmp_54;
  real_T tmp_55;
  real_T tmp_56;
  real_T tmp_57;
  real_T tmp_58;
  real_T tmp_59;
  real_T tmp_5a;
  real_T tmp_5b;
  real_T tmp_5c;
  real_T tmp_5d;
  real_T tmp_5e;
  real_T tmp_5f;
  real_T tmp_5g;
  real_T tmp_5h;
  real_T tmp_5i;
  real_T tmp_5j;
  real_T tmp_5k;
  real_T tmp_5l;
  real_T tmp_5m;
  real_T tmp_5n;
  real_T tmp_5o;
  real_T tmp_5p;
  real_T tmp_5q;
  real_T tmp_5r;
  real_T tmp_5s;
  real_T tmp_5t;
  real_T tmp_5u;
  real_T tmp_5v;
  real_T tmp_5w;
  real_T tmp_5x;
  real_T tmp_5y;
  real_T tmp_5z;
  real_T tmp_6;
  real_T tmp_60;
  real_T tmp_61;
  real_T tmp_62;
  real_T tmp_63;
  real_T tmp_64;
  real_T tmp_65;
  real_T tmp_66;
  real_T tmp_67;
  real_T tmp_68;
  real_T tmp_69;
  real_T tmp_6a;
  real_T tmp_6b;
  real_T tmp_6c;
  real_T tmp_6d;
  real_T tmp_6e;
  real_T tmp_6f;
  real_T tmp_6g;
  real_T tmp_6h;
  real_T tmp_6i;
  real_T tmp_6j;
  real_T tmp_6k;
  real_T tmp_6l;
  real_T tmp_6m;
  real_T tmp_6n;
  real_T tmp_6o;
  real_T tmp_6p;
  real_T tmp_6q;
  real_T tmp_6r;
  real_T tmp_6s;
  real_T tmp_6t;
  real_T tmp_6u;
  real_T tmp_6v;
  real_T tmp_6w;
  real_T tmp_6x;
  real_T tmp_6y;
  real_T tmp_6z;
  real_T tmp_7;
  real_T tmp_70;
  real_T tmp_71;
  real_T tmp_72;
  real_T tmp_73;
  real_T tmp_74;
  real_T tmp_75;
  real_T tmp_76;
  real_T tmp_77;
  real_T tmp_78;
  real_T tmp_79;
  real_T tmp_7a;
  real_T tmp_7b;
  real_T tmp_7c;
  real_T tmp_7d;
  real_T tmp_7e;
  real_T tmp_7f;
  real_T tmp_7g;
  real_T tmp_7h;
  real_T tmp_7i;
  real_T tmp_7j;
  real_T tmp_7k;
  real_T tmp_7l;
  real_T tmp_7m;
  real_T tmp_7n;
  real_T tmp_7o;
  real_T tmp_7p;
  real_T tmp_7q;
  real_T tmp_7r;
  real_T tmp_7s;
  real_T tmp_7t;
  real_T tmp_7u;
  real_T tmp_7v;
  real_T tmp_7w;
  real_T tmp_7x;
  real_T tmp_7y;
  real_T tmp_7z;
  real_T tmp_8;
  real_T tmp_80;
  real_T tmp_81;
  real_T tmp_82;
  real_T tmp_83;
  real_T tmp_84;
  real_T tmp_85;
  real_T tmp_86;
  real_T tmp_87;
  real_T tmp_88;
  real_T tmp_89;
  real_T tmp_8a;
  real_T tmp_8b;
  real_T tmp_8c;
  real_T tmp_8d;
  real_T tmp_8e;
  real_T tmp_8f;
  real_T tmp_8g;
  real_T tmp_8h;
  real_T tmp_8i;
  real_T tmp_8j;
  real_T tmp_8k;
  real_T tmp_8l;
  real_T tmp_8m;
  real_T tmp_8n;
  real_T tmp_8o;
  real_T tmp_8p;
  real_T tmp_8q;
  real_T tmp_8r;
  real_T tmp_8s;
  real_T tmp_8t;
  real_T tmp_8u;
  real_T tmp_8v;
  real_T tmp_8w;
  real_T tmp_8x;
  real_T tmp_8y;
  real_T tmp_8z;
  real_T tmp_9;
  real_T tmp_90;
  real_T tmp_91;
  real_T tmp_92;
  real_T tmp_93;
  real_T tmp_94;
  real_T tmp_95;
  real_T tmp_96;
  real_T tmp_97;
  real_T tmp_98;
  real_T tmp_99;
  real_T tmp_9a;
  real_T tmp_9b;
  real_T tmp_9c;
  real_T tmp_9d;
  real_T tmp_9e;
  real_T tmp_9f;
  real_T tmp_9g;
  real_T tmp_9h;
  real_T tmp_9i;
  real_T tmp_9j;
  real_T tmp_9k;
  real_T tmp_9l;
  real_T tmp_9m;
  real_T tmp_9n;
  real_T tmp_9o;
  real_T tmp_9p;
  real_T tmp_9q;
  real_T tmp_9r;
  real_T tmp_9s;
  real_T tmp_9t;
  real_T tmp_9u;
  real_T tmp_9v;
  real_T tmp_9w;
  real_T tmp_9x;
  real_T tmp_9y;
  real_T tmp_9z;
  real_T tmp_a;
  real_T tmp_a0;
  real_T tmp_a1;
  real_T tmp_a2;
  real_T tmp_a3;
  real_T tmp_a4;
  real_T tmp_a5;
  real_T tmp_a6;
  real_T tmp_a7;
  real_T tmp_a8;
  real_T tmp_a9;
  real_T tmp_aa;
  real_T tmp_ab;
  real_T tmp_ac;
  real_T tmp_ad;
  real_T tmp_ae;
  real_T tmp_af;
  real_T tmp_ag;
  real_T tmp_ah;
  real_T tmp_ai;
  real_T tmp_aj;
  real_T tmp_ak;
  real_T tmp_al;
  real_T tmp_am;
  real_T tmp_an;
  real_T tmp_ao;
  real_T tmp_ap;
  real_T tmp_aq;
  real_T tmp_ar;
  real_T tmp_as;
  real_T tmp_at;
  real_T tmp_au;
  real_T tmp_av;
  real_T tmp_aw;
  real_T tmp_ax;
  real_T tmp_ay;
  real_T tmp_az;
  real_T tmp_b;
  real_T tmp_b0;
  real_T tmp_b1;
  real_T tmp_b2;
  real_T tmp_b3;
  real_T tmp_b4;
  real_T tmp_b5;
  real_T tmp_b6;
  real_T tmp_b7;
  real_T tmp_b8;
  real_T tmp_b9;
  real_T tmp_ba;
  real_T tmp_bb;
  real_T tmp_bc;
  real_T tmp_bd;
  real_T tmp_be;
  real_T tmp_bf;
  real_T tmp_bg;
  real_T tmp_bh;
  real_T tmp_bi;
  real_T tmp_bj;
  real_T tmp_bk;
  real_T tmp_bl;
  real_T tmp_bm;
  real_T tmp_bn;
  real_T tmp_bo;
  real_T tmp_bp;
  real_T tmp_bq;
  real_T tmp_br;
  real_T tmp_bs;
  real_T tmp_bt;
  real_T tmp_bu;
  real_T tmp_bv;
  real_T tmp_bw;
  real_T tmp_bx;
  real_T tmp_by;
  real_T tmp_bz;
  real_T tmp_c;
  real_T tmp_c0;
  real_T tmp_c1;
  real_T tmp_c2;
  real_T tmp_c3;
  real_T tmp_c4;
  real_T tmp_c5;
  real_T tmp_c6;
  real_T tmp_c7;
  real_T tmp_c8;
  real_T tmp_c9;
  real_T tmp_ca;
  real_T tmp_cb;
  real_T tmp_cc;
  real_T tmp_cd;
  real_T tmp_ce;
  real_T tmp_cf;
  real_T tmp_cg;
  real_T tmp_ch;
  real_T tmp_ci;
  real_T tmp_cj;
  real_T tmp_ck;
  real_T tmp_cl;
  real_T tmp_cm;
  real_T tmp_cn;
  real_T tmp_co;
  real_T tmp_cp;
  real_T tmp_cq;
  real_T tmp_cr;
  real_T tmp_cs;
  real_T tmp_ct;
  real_T tmp_cu;
  real_T tmp_cv;
  real_T tmp_cw;
  real_T tmp_cx;
  real_T tmp_cy;
  real_T tmp_cz;
  real_T tmp_d;
  real_T tmp_d0;
  real_T tmp_d1;
  real_T tmp_d2;
  real_T tmp_d3;
  real_T tmp_d4;
  real_T tmp_d5;
  real_T tmp_d6;
  real_T tmp_d7;
  real_T tmp_d8;
  real_T tmp_d9;
  real_T tmp_da;
  real_T tmp_db;
  real_T tmp_dc;
  real_T tmp_dd;
  real_T tmp_de;
  real_T tmp_df;
  real_T tmp_dg;
  real_T tmp_dh;
  real_T tmp_di;
  real_T tmp_dj;
  real_T tmp_dk;
  real_T tmp_dl;
  real_T tmp_dm;
  real_T tmp_dn;
  real_T tmp_do;
  real_T tmp_dp;
  real_T tmp_dq;
  real_T tmp_dr;
  real_T tmp_ds;
  real_T tmp_dt;
  real_T tmp_du;
  real_T tmp_dv;
  real_T tmp_dw;
  real_T tmp_dx;
  real_T tmp_dy;
  real_T tmp_dz;
  real_T tmp_e;
  real_T tmp_e0;
  real_T tmp_e1;
  real_T tmp_e2;
  real_T tmp_e3;
  real_T tmp_e4;
  real_T tmp_e5;
  real_T tmp_e6;
  real_T tmp_e7;
  real_T tmp_e8;
  real_T tmp_e9;
  real_T tmp_ea;
  real_T tmp_eb;
  real_T tmp_ec;
  real_T tmp_ed;
  real_T tmp_ee;
  real_T tmp_ef;
  real_T tmp_eg;
  real_T tmp_eh;
  real_T tmp_ei;
  real_T tmp_ej;
  real_T tmp_ek;
  real_T tmp_el;
  real_T tmp_em;
  real_T tmp_en;
  real_T tmp_eo;
  real_T tmp_ep;
  real_T tmp_eq;
  real_T tmp_er;
  real_T tmp_es;
  real_T tmp_et;
  real_T tmp_eu;
  real_T tmp_ev;
  real_T tmp_ew;
  real_T tmp_ex;
  real_T tmp_ey;
  real_T tmp_ez;
  real_T tmp_f;
  real_T tmp_f0;
  real_T tmp_f1;
  real_T tmp_f2;
  real_T tmp_f3;
  real_T tmp_f4;
  real_T tmp_f5;
  real_T tmp_f6;
  real_T tmp_f7;
  real_T tmp_f8;
  real_T tmp_f9;
  real_T tmp_fa;
  real_T tmp_fb;
  real_T tmp_fc;
  real_T tmp_fd;
  real_T tmp_fe;
  real_T tmp_ff;
  real_T tmp_fg;
  real_T tmp_fh;
  real_T tmp_fi;
  real_T tmp_fj;
  real_T tmp_fk;
  real_T tmp_fl;
  real_T tmp_fm;
  real_T tmp_fn;
  real_T tmp_fo;
  real_T tmp_fp;
  real_T tmp_fq;
  real_T tmp_fr;
  real_T tmp_fs;
  real_T tmp_ft;
  real_T tmp_fu;
  real_T tmp_fv;
  real_T tmp_fw;
  real_T tmp_fx;
  real_T tmp_fy;
  real_T tmp_fz;
  real_T tmp_g;
  real_T tmp_g0;
  real_T tmp_g1;
  real_T tmp_g2;
  real_T tmp_g3;
  real_T tmp_g4;
  real_T tmp_g5;
  real_T tmp_g6;
  real_T tmp_g7;
  real_T tmp_g8;
  real_T tmp_g9;
  real_T tmp_ga;
  real_T tmp_gb;
  real_T tmp_gc;
  real_T tmp_gd;
  real_T tmp_ge;
  real_T tmp_gf;
  real_T tmp_gg;
  real_T tmp_gh;
  real_T tmp_gi;
  real_T tmp_gj;
  real_T tmp_gk;
  real_T tmp_gl;
  real_T tmp_gm;
  real_T tmp_gn;
  real_T tmp_go;
  real_T tmp_gp;
  real_T tmp_gq;
  real_T tmp_gr;
  real_T tmp_gs;
  real_T tmp_gt;
  real_T tmp_gu;
  real_T tmp_gv;
  real_T tmp_gw;
  real_T tmp_gx;
  real_T tmp_gy;
  real_T tmp_gz;
  real_T tmp_h;
  real_T tmp_h0;
  real_T tmp_h1;
  real_T tmp_h2;
  real_T tmp_h3;
  real_T tmp_h4;
  real_T tmp_h5;
  real_T tmp_h6;
  real_T tmp_h7;
  real_T tmp_h8;
  real_T tmp_h9;
  real_T tmp_ha;
  real_T tmp_hb;
  real_T tmp_hc;
  real_T tmp_hd;
  real_T tmp_he;
  real_T tmp_hf;
  real_T tmp_hg;
  real_T tmp_hh;
  real_T tmp_hi;
  real_T tmp_hj;
  real_T tmp_hk;
  real_T tmp_hl;
  real_T tmp_hm;
  real_T tmp_hn;
  real_T tmp_ho;
  real_T tmp_hp;
  real_T tmp_hq;
  real_T tmp_hz;
  real_T tmp_i;
  real_T tmp_i0;
  real_T tmp_i1;
  real_T tmp_i2;
  real_T tmp_j;
  real_T tmp_k;
  real_T tmp_l;
  real_T tmp_m;
  real_T tmp_n;
  real_T tmp_o;
  real_T tmp_p;
  real_T tmp_q;
  real_T tmp_r;
  real_T tmp_s;
  real_T tmp_t;
  real_T tmp_u;
  real_T tmp_v;
  real_T tmp_w;
  real_T tmp_x;
  real_T tmp_y;
  real_T tmp_z;
  real_T u_a;
  real_T v_a;
  real_T w_a;
  real_T x_a;
  real_T y_a;
  int32_T b_ix;
  int32_T c_ix;
  int32_T d;
  int32_T d_k;
  int32_T i;
  int32_T ix;
  int32_T iy;
  int32_T jj;
  int32_T jy;
  int8_T ipiv[8];
  int8_T p[8];
  int8_T ipiv_0;

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  /* :  DM = DMatrix(q, HexaConstants, ArmConstants); */
  /* 'DMatrix:3' mb  = HexaConstants.Mass; */
  /* 'DMatrix:4' ml1 = ArmConstants.Mass1; */
  /* 'DMatrix:5' ml2 = ArmConstants.Mass2; */
  /* 'DMatrix:7' L   = ArmConstants.Hexa_to_joint_L; */
  /* 'DMatrix:9' l1  = ArmConstants.l1_dim(1); */
  /* 'DMatrix:11' c1  = ArmConstants.MC1; */
  /* 'DMatrix:12' c2  = ArmConstants.MC2; */
  /* 'DMatrix:14' Hb = HexaConstants.Inertia; */
  /* 'DMatrix:15' Hbx = Hb(1, 1); */
  /* 'DMatrix:15' Hby = Hb(2, 2); */
  /* 'DMatrix:15' Hbz = Hb(3, 3); */
  /* 'DMatrix:17' H1 = ArmConstants.Inertia1; */
  /* 'DMatrix:18' H1xx = H1(1, 1); */
  /* 'DMatrix:18' H1yy = H1(2, 2); */
  /* 'DMatrix:18' H1zz = H1(3, 3); */
  /* 'DMatrix:19' H1xy = H1(1, 2); */
  /* 'DMatrix:19' H1yz = H1(2, 3); */
  /* 'DMatrix:19' H1zx = H1(1, 3); */
  /* 'DMatrix:21' H2 = ArmConstants.Inertia2; */
  /* 'DMatrix:22' H2xx = H2(1, 1); */
  /* 'DMatrix:22' H2yy = H2(2, 2); */
  /* 'DMatrix:22' H2zz = H2(3, 3); */
  /* 'DMatrix:23' H2xy = H2(1, 2); */
  /* 'DMatrix:23' H2yz = H2(2, 3); */
  /* 'DMatrix:23' H2zx = H2(1, 3); */
  /* 'DMatrix:25' phi = xi(4); */
  /* 'DMatrix:26' th  = xi(5); */
  /* 'DMatrix:27' psi = xi(6); */
  /* 'DMatrix:28' q1  = xi(7); */
  /* 'DMatrix:29' q2  = xi(8); */
  /* 'DMatrix:31' [D11, D12, D13, D14, D15, D16, D17, D18] = get_D1(); */
  /* 'DMatrix:50' D11=mb+ml1+ml2; */
  /* 'DMatrix:51' D12=0; */
  /* 'DMatrix:52' D13=0; */
  /* 'DMatrix:53' D14=sin(phi)*(sin(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))+ ... */
  /* 'DMatrix:54'   cos(psi)*(L*(ml1+ml2)+c2*ml2*cos(q1+q2))*sin(th))+cos(phi)*(- ... */
  /* 'DMatrix:55'   L*(ml1+ml2)*sin(psi)+c2*ml2*sin(psi)*sin(q1)*sin(q2)+cos(psi)*( ... */
  /* 'DMatrix:56'   c1*ml1+l1*ml2+c2*ml2*cos(q2))*sin(q1)*sin(th))+cos(q1)*((c1*ml1+ ... */
  /* 'DMatrix:57'   l1*ml2)*cos(psi)*sin(phi)*sin(th)+cos(phi)*(-(c1*ml1+l1*ml2+ ... */
  /* 'DMatrix:58'   c2*ml2*cos(q2))*sin(psi)+c2*ml2*cos(psi)*sin(q2)*sin(th))); */
  smax_tmp = rtu_InBus1_Positions[6] + rtu_InBus1_Positions[7];
  smax = std::sin(smax_tmp);
  s = std::cos(smax_tmp);
  D14_tmp = rtP_ArmConstants.MC2 * rtP_ArmConstants.Mass2;
  D14_tmp_tmp = rtP_ArmConstants.MC1 * rtP_ArmConstants.Mass1;
  D14_tmp_0 = rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 + D14_tmp_tmp;
  D14_tmp_1 = rtP_ArmConstants.Mass1 + rtP_ArmConstants.Mass2;
  D14_tmp_2 = D14_tmp_1 * rtP_ArmConstants.Hexa_to_joint_L;
  D14_tmp_3 = D14_tmp * s;
  D14_tmp_4 = D14_tmp * smax;
  D14_tmp_5 = D14_tmp_1 * -rtP_ArmConstants.Hexa_to_joint_L;
  D14 = (((D14_tmp * std::cos(rtu_InBus1_Positions[7]) + D14_tmp_0) * std::cos
          (rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[6]) * std::
          sin(rtu_InBus1_Positions[4]) + (D14_tmp * std::sin
           (rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[6]) * std::
           sin(rtu_InBus1_Positions[7]) + D14_tmp_5 * std::sin
           (rtu_InBus1_Positions[5]))) * std::cos(rtu_InBus1_Positions[3]) +
         ((D14_tmp_0 * std::sin(rtu_InBus1_Positions[6]) + D14_tmp_4) * std::sin
          (rtu_InBus1_Positions[5]) + (D14_tmp_2 + D14_tmp_3) * std::cos
          (rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[4])) * std::
         sin(rtu_InBus1_Positions[3])) + ((-(D14_tmp * std::cos
    (rtu_InBus1_Positions[7]) + D14_tmp_0) * std::sin(rtu_InBus1_Positions[5]) +
    D14_tmp * std::cos(rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions
    [7]) * std::sin(rtu_InBus1_Positions[4])) * std::cos(rtu_InBus1_Positions[3])
    + D14_tmp_0 * std::cos(rtu_InBus1_Positions[5]) * std::sin
    (rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[4])) * std::cos
    (rtu_InBus1_Positions[6]);

  /* 'DMatrix:59' D15=-cos(psi)*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+ ... */
  /* 'DMatrix:60'   c2*ml2*cos(phi+q1+q2))*cos(th); */
  D15_tmp_tmp = rtu_InBus1_Positions[3] + rtu_InBus1_Positions[6];
  D15_tmp = std::cos(D15_tmp_tmp);
  D15_tmp_tmp_0 = D15_tmp_tmp + rtu_InBus1_Positions[7];
  D15_tmp_0 = std::cos(D15_tmp_tmp_0);
  D15_tmp_1 = D14_tmp_0 * D15_tmp;
  D15_tmp_2 = D14_tmp * D15_tmp_0;
  D15 = ((D14_tmp_2 * std::cos(rtu_InBus1_Positions[3]) + D15_tmp_1) + D15_tmp_2)
    * -std::cos(rtu_InBus1_Positions[5]) * std::cos(rtu_InBus1_Positions[4]);

  /* 'DMatrix:61' D16=cos(phi)*(-cos(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+ ... */
  /* 'DMatrix:62'   q2))+(L*(ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin( ... */
  /* 'DMatrix:63'   psi)*sin(th))+-sin(phi)*(cos(psi)*(L*(ml1+ml2)+(c1*ml1+l1* ... */
  /* 'DMatrix:64'   ml2)*cos(q1)+c2*ml2*cos(q1+q2))+sin(psi)*((c1*ml1+l1*ml2)*sin(q1) ... */
  /* 'DMatrix:65'   +c2*ml2*sin(q1+q2))*sin(th)); */
  D16 = (((D14_tmp_0 * std::cos(rtu_InBus1_Positions[6]) + D14_tmp_2) +
          D14_tmp_3) * std::sin(rtu_InBus1_Positions[5]) * std::sin
         (rtu_InBus1_Positions[4]) + (D14_tmp_0 * std::sin(rtu_InBus1_Positions
           [6]) + D14_tmp_4) * -std::cos(rtu_InBus1_Positions[5])) * std::cos
    (rtu_InBus1_Positions[3]) + (((D14_tmp_0 * std::cos(rtu_InBus1_Positions[6])
    + D14_tmp_2) + D14_tmp_3) * std::cos(rtu_InBus1_Positions[5]) + (D14_tmp_0 *
    std::sin(rtu_InBus1_Positions[6]) + D14_tmp_4) * std::sin
    (rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[4])) * -std::sin
    (rtu_InBus1_Positions[3]);

  /* 'DMatrix:66' D17=ml2*(l1*sin(q1)+c2*sin(q1+q2))*(sin(phi)*sin(psi)+cos(phi)*cos( ... */
  /* 'DMatrix:67'   psi)*sin(th))+c1*ml1*sin(phi)*(sin(psi)*sin(q1)+cos(psi)*cos(q1)* ... */
  /* 'DMatrix:68'   sin(th))+ml2*(l1*cos(q1)+c2*cos(q1+q2))*(-cos(phi)*sin(psi)+ ... */
  /* 'DMatrix:69'   cos(psi)*sin(phi)*sin(th))+c1*ml1*cos(phi)*(-cos(q1)*sin(psi) ... */
  /* 'DMatrix:70'   +cos(psi)*sin(q1)*sin(th)); */
  D17_tmp = rtP_ArmConstants.MC2 * smax;
  D17_tmp_0 = rtP_ArmConstants.MC2 * s;
  D17 = (((rtP_ArmConstants.l1_dim * std::sin(rtu_InBus1_Positions[6]) + D17_tmp)
          * rtP_ArmConstants.Mass2 * (std::cos(rtu_InBus1_Positions[3]) * std::
           cos(rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[4]) +
           std::sin(rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5]))
          + (std::cos(rtu_InBus1_Positions[5]) * std::cos(rtu_InBus1_Positions[6])
             * std::sin(rtu_InBus1_Positions[4]) + std::sin
             (rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[6])) *
          (D14_tmp_tmp * std::sin(rtu_InBus1_Positions[3]))) +
         (rtP_ArmConstants.l1_dim * std::cos(rtu_InBus1_Positions[6]) +
          D17_tmp_0) * rtP_ArmConstants.Mass2 * (std::cos(rtu_InBus1_Positions[5])
          * std::sin(rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[4])
          + -std::cos(rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5])))
    + (std::cos(rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[6]) *
       std::sin(rtu_InBus1_Positions[4]) + -std::cos(rtu_InBus1_Positions[6]) *
       std::sin(rtu_InBus1_Positions[5])) * (D14_tmp_tmp * std::cos
    (rtu_InBus1_Positions[3]));

  /* 'DMatrix:71' D18=ml2*(c2*sin(q1+q2)*(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))+ ... */
  /* 'DMatrix:72'   c2*cos(q1+q2)*(-cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th))); */
  D18 = ((std::cos(rtu_InBus1_Positions[3]) * std::cos(rtu_InBus1_Positions[5]) *
          std::sin(rtu_InBus1_Positions[4]) + std::sin(rtu_InBus1_Positions[3]) *
          std::sin(rtu_InBus1_Positions[5])) * D17_tmp + (std::cos
          (rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[3]) * std::
          sin(rtu_InBus1_Positions[4]) + -std::cos(rtu_InBus1_Positions[3]) *
          std::sin(rtu_InBus1_Positions[5])) * D17_tmp_0) *
    rtP_ArmConstants.Mass2;

  /* 'DMatrix:32' [D22, D23, D24, D25, D26, D27, D28] = get_D2(); */
  /* 'DMatrix:76' D22=mb+ml1+ml2; */
  /* 'DMatrix:77' D23=0; */
  /* 'DMatrix:78' D24=ml2*cos(psi)*(L*cos(phi)+l1*cos(phi+q1)+c2*cos(phi+q1+q2))*cos(th) ... */
  /* 'DMatrix:79'   ^2+ml1*sin(phi)*(-c1*cos(psi)*sin(q1)+(L+c1*cos(q1))*sin( ... */
  /* 'DMatrix:80'   psi)*sin(th))+ml1*cos(phi)*(cos(psi)*(L+c1*cos(q1))+c1*sin(psi)* ... */
  /* 'DMatrix:81'   sin(q1)*sin(th))+ml2*sin(th)*((L+l1*cos(q1)+c2*cos(q1+q2))*(sin( ... */
  /* 'DMatrix:82'   phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))-(l1*sin(q1)+c2*sin( ... */
  /* 'DMatrix:83'   q1+q2))*(-cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th))); */
  a = std::cos(rtu_InBus1_Positions[4]);
  D24_tmp = rtP_ArmConstants.l1_dim * D15_tmp;
  D24_tmp_0 = rtP_ArmConstants.MC2 * D15_tmp_0;
  D24 = ((((rtP_ArmConstants.MC1 * std::cos(rtu_InBus1_Positions[6]) +
            rtP_ArmConstants.Hexa_to_joint_L) * std::sin(rtu_InBus1_Positions[5])
           * std::sin(rtu_InBus1_Positions[4]) + -rtP_ArmConstants.MC1 * std::
           cos(rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[6])) *
          (rtP_ArmConstants.Mass1 * std::sin(rtu_InBus1_Positions[3])) +
          ((rtP_ArmConstants.Hexa_to_joint_L * std::cos(rtu_InBus1_Positions[3])
            + D24_tmp) + D24_tmp_0) * (rtP_ArmConstants.Mass2 * std::cos
           (rtu_InBus1_Positions[5])) * (a * a)) + ((rtP_ArmConstants.MC1 * std::
           cos(rtu_InBus1_Positions[6]) + rtP_ArmConstants.Hexa_to_joint_L) *
          std::cos(rtu_InBus1_Positions[5]) + rtP_ArmConstants.MC1 * std::sin
          (rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[6]) * std::
          sin(rtu_InBus1_Positions[4])) * (rtP_ArmConstants.Mass1 * std::cos
          (rtu_InBus1_Positions[3]))) + (((rtP_ArmConstants.l1_dim * std::cos
    (rtu_InBus1_Positions[6]) + rtP_ArmConstants.Hexa_to_joint_L) + D17_tmp_0) *
    (std::cos(rtu_InBus1_Positions[3]) * std::cos(rtu_InBus1_Positions[5]) * std::
     sin(rtu_InBus1_Positions[4]) + std::sin(rtu_InBus1_Positions[3]) * std::sin
     (rtu_InBus1_Positions[5])) - (std::cos(rtu_InBus1_Positions[5]) * std::sin
    (rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[4]) + -std::cos
    (rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5])) *
    (rtP_ArmConstants.l1_dim * std::sin(rtu_InBus1_Positions[6]) + D17_tmp)) *
    (rtP_ArmConstants.Mass2 * std::sin(rtu_InBus1_Positions[4]));

  /* 'DMatrix:84' D25=-(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2* ... */
  /* 'DMatrix:85'   cos(phi+q1+q2))*cos(th)*sin(psi); */
  D25 = -((D14_tmp_2 * std::cos(rtu_InBus1_Positions[3]) + D15_tmp_1) +
          D15_tmp_2) * std::cos(rtu_InBus1_Positions[4]) * std::sin
    (rtu_InBus1_Positions[5]);

  /* 'DMatrix:86' D26=-ml1*(L+c1*cos(q1))*(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin( ... */
  /* 'DMatrix:87'   th))-ml2*(L+l1*cos(q1)+c2*cos(q1+q2))*(sin(phi)*sin(psi)+cos( ... */
  /* 'DMatrix:88'   phi)*cos(psi)*sin(th))+c1*ml1*sin(q1)*(-cos(phi)*sin(psi)+ ... */
  /* 'DMatrix:89'   cos(psi)*sin(phi)*sin(th))+ml2*(l1*sin(q1)+c2*sin(q1+q2))*(- ... */
  /* 'DMatrix:90'   cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th)); */
  D14_tmp_tmp = (((rtP_ArmConstants.MC1 * std::cos(rtu_InBus1_Positions[6]) +
                   rtP_ArmConstants.Hexa_to_joint_L) * -rtP_ArmConstants.Mass1 *
                  (std::cos(rtu_InBus1_Positions[3]) * std::cos
                   (rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[4])
                   + std::sin(rtu_InBus1_Positions[3]) * std::sin
                   (rtu_InBus1_Positions[5])) - ((rtP_ArmConstants.l1_dim * std::
    cos(rtu_InBus1_Positions[6]) + rtP_ArmConstants.Hexa_to_joint_L) + D17_tmp_0)
                  * rtP_ArmConstants.Mass2 * (std::cos(rtu_InBus1_Positions[3]) *
    std::cos(rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[4]) + std::
    sin(rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5]))) + (std::
    cos(rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[3]) * std::sin
    (rtu_InBus1_Positions[4]) + -std::cos(rtu_InBus1_Positions[3]) * std::sin
    (rtu_InBus1_Positions[5])) * (D14_tmp_tmp * std::sin(rtu_InBus1_Positions[6])))
    + (rtP_ArmConstants.l1_dim * std::sin(rtu_InBus1_Positions[6]) + D17_tmp) *
    rtP_ArmConstants.Mass2 * (std::cos(rtu_InBus1_Positions[5]) * std::sin
    (rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[4]) + -std::cos
    (rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5]));

  /* 'DMatrix:91' D27=-((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))*(cos(psi)*sin( ... */
  /* 'DMatrix:92'   phi)-cos(phi)*sin(psi)*sin(th))+(c1*ml1+l1*ml2)*cos(q1)*( ... */
  /* 'DMatrix:93'   cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th))+c2*ml2*cos(q1+q2)*( ... */
  /* 'DMatrix:94'   cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th)); */
  D27 = ((std::cos(rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[3])
          - std::cos(rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5])
          * std::sin(rtu_InBus1_Positions[4])) * -(D14_tmp_0 * std::sin
          (rtu_InBus1_Positions[6]) + D14_tmp_4) + (std::sin
          (rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5]) * std::
          sin(rtu_InBus1_Positions[4]) + std::cos(rtu_InBus1_Positions[3]) * std::
          cos(rtu_InBus1_Positions[5])) * (D14_tmp_0 * std::cos
          (rtu_InBus1_Positions[6]))) + (std::sin(rtu_InBus1_Positions[3]) * std::
    sin(rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[4]) + std::cos
    (rtu_InBus1_Positions[3]) * std::cos(rtu_InBus1_Positions[5])) * D14_tmp_3;

  /* 'DMatrix:95' D28=ml2*(c2*sin(q1+q2)*(-cos(psi)*sin(phi)+cos(phi)*sin(psi)*sin( ... */
  /* 'DMatrix:96'   th))+c2*cos(q1+q2)*(cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th))); */
  D28 = ((std::cos(rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5]) *
          std::sin(rtu_InBus1_Positions[4]) + -std::cos(rtu_InBus1_Positions[5])
          * std::sin(rtu_InBus1_Positions[3])) * D17_tmp + (std::sin
          (rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5]) * std::
          sin(rtu_InBus1_Positions[4]) + std::cos(rtu_InBus1_Positions[3]) * std::
          cos(rtu_InBus1_Positions[5])) * D17_tmp_0) * rtP_ArmConstants.Mass2;

  /* 'DMatrix:33' [D33, D34, D35, D36, D37, D38] = get_D3(); */
  /* 'DMatrix:100' D33=mb+ml1+ml2; */
  /* 'DMatrix:101' D34=cos(th)*(L*(ml1+ml2)*sin(phi)+(c1*ml1+l1*ml2)*sin(phi+q1)+c2* ... */
  /* 'DMatrix:102'   ml2*sin(phi+q1+q2)); */
  a = std::sin(D15_tmp_tmp);
  D34_tmp = std::sin(D15_tmp_tmp_0);
  D34_tmp_0 = D14_tmp_0 * a;
  D34_tmp_1 = D14_tmp * D34_tmp;
  D34 = ((D14_tmp_2 * std::sin(rtu_InBus1_Positions[3]) + D34_tmp_0) + D34_tmp_1)
    * std::cos(rtu_InBus1_Positions[4]);

  /* 'DMatrix:103' D35=(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+ ... */
  /* 'DMatrix:104'   q1+q2))*sin(th); */
  D35 = ((D14_tmp_2 * std::cos(rtu_InBus1_Positions[3]) + D15_tmp_1) + D15_tmp_2)
    * std::sin(rtu_InBus1_Positions[4]);

  /* 'DMatrix:105' D36=0; */
  /* 'DMatrix:106' D37=cos(th)*((c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2)); */
  D37_tmp = D34_tmp_0 + D34_tmp_1;
  D37 = D37_tmp * std::cos(rtu_InBus1_Positions[4]);

  /* 'DMatrix:107' D38=c2*ml2*cos(th)*sin(phi+q1+q2); */
  D38 = D14_tmp * std::cos(rtu_InBus1_Positions[4]) * D34_tmp;

  /* 'DMatrix:34' [D44, D45, D46, D47, D48] = get_D4(); */
  /* 'DMatrix:111' D44=H1zz+H2zz+Hbx+c1^2*ml1+L^2*ml1+c2^2*ml2+L^2*ml2+l1^2*ml2+2* ... */
  /* 'DMatrix:112'   L*(c1*ml1+l1*ml2)*cos(q1)+2*c2*l1*ml2*cos(q2)+2*c2*L*ml2* ... */
  /* 'DMatrix:113'   cos(q1+q2); */
  /* 'DMatrix:114' D45=H1yz*cos(phi+q1)+H2yz*cos(phi+q1+q2)+H1zx*sin(phi+q1)+H2zx*sin(phi+ ... */
  /* 'DMatrix:115'   q1+q2); */
  D45_tmp = rtP_ArmConstants.Inertia2[7] * D15_tmp_0;
  D45_tmp_0 = rtP_ArmConstants.Inertia2[6] * D34_tmp;
  D45_tmp_1 = ((rtP_ArmConstants.Inertia1[7] * D15_tmp + D45_tmp) +
               rtP_ArmConstants.Inertia1[6] * a) + D45_tmp_0;
  D45 = D45_tmp_1;

  /* 'DMatrix:116' D46=(1/2)*(-H1zx*cos(phi+q1-th)-H2zx*cos(phi+q1+q2+(-1) ... */
  /* 'DMatrix:117'   *th)-H1zx*cos(phi+q1+th)-H2zx*cos(phi+q1+q2+th)+2*c1* ... */
  /* 'DMatrix:118'   L*ml1*sin(q1-th)+2*L*l1*ml2*sin(q1-th)+H1yz*sin(phi+ ... */
  /* 'DMatrix:119'   q1-th)+2*c2*l1*ml2*sin(q2-th)+2*c2*L*ml2*sin(q1+q2+( ... */
  /* 'DMatrix:120'   -1)*th)+H2yz*sin(phi+q1+q2-th)+(-2)*H1zz*sin(th)+(-2)*H2zz* ... */
  /* 'DMatrix:121'   sin(th)+(-2)*Hbx*sin(th)+(-2)*c1^2*ml1*sin(th)+(-2)*L^2*ml1* ... */
  /* 'DMatrix:122'   sin(th)+(-2)*c2^2*ml2*sin(th)+(-2)*L^2*ml2*sin(th)+(-2)*l1^2* ... */
  /* 'DMatrix:123'   ml2*sin(th)+(-2)*c1*L*ml1*sin(q1+th)+(-2)*L*l1*ml2*sin(q1+th)+ ... */
  /* 'DMatrix:124'   H1yz*sin(phi+q1+th)+(-2)*c2*l1*ml2*sin(q2+th)+(-2)*c2*L*ml2* ... */
  /* 'DMatrix:125'   sin(q1+q2+th)+H2yz*sin(phi+q1+q2+th)); */
  D46_tmp_tmp_7 = rtu_InBus1_Positions[6] - rtu_InBus1_Positions[4];
  D46_tmp = std::sin(D46_tmp_tmp_7);
  D46_tmp_tmp_6 = rtu_InBus1_Positions[4] + rtu_InBus1_Positions[6];
  D46_tmp_0 = std::sin(D46_tmp_tmp_6);
  D46_tmp_tmp = D15_tmp_tmp - rtu_InBus1_Positions[4];
  D46_tmp_1 = std::cos(D46_tmp_tmp);
  D46_tmp_tmp_0 = D15_tmp_tmp_0 - rtu_InBus1_Positions[4];
  D46_tmp_2 = std::cos(D46_tmp_tmp_0);
  D46_tmp_tmp_1 = D15_tmp_tmp + rtu_InBus1_Positions[4];
  D46_tmp_3 = std::cos(D46_tmp_tmp_1);
  D46_tmp_tmp_2 = D15_tmp_tmp_0 + rtu_InBus1_Positions[4];
  D46_tmp_4 = std::cos(D46_tmp_tmp_2);
  D46_tmp_5 = std::sin(D46_tmp_tmp);
  D46_tmp_6 = std::sin(D46_tmp_tmp_0);
  D46_tmp_7 = std::sin(D46_tmp_tmp_1);
  D46_tmp_8 = std::sin(D46_tmp_tmp_2);
  D46_tmp_tmp_8 = rtu_InBus1_Positions[7] - rtu_InBus1_Positions[4];
  D46_tmp_9 = std::sin(D46_tmp_tmp_8);
  D46_tmp_tmp_9 = smax_tmp - rtu_InBus1_Positions[4];
  D46_tmp_a = std::sin(D46_tmp_tmp_9);
  D46_tmp_tmp_a = rtu_InBus1_Positions[4] + rtu_InBus1_Positions[7];
  D46_tmp_b = std::sin(D46_tmp_tmp_a);
  D46_tmp_tmp_b = smax_tmp + rtu_InBus1_Positions[4];
  D46_tmp_c = std::sin(D46_tmp_tmp_b);
  D46_tmp_d = 2.0 * rtP_ArmConstants.MC2;
  D46_tmp_tmp_3 = rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Hexa_to_joint_L;
  D46_tmp_e = D46_tmp_tmp_3 * -2.0;
  D46_tmp_f = -2.0 * rtP_ArmConstants.MC2;
  D46_tmp_g = rtP_ArmConstants.MC1 * rtP_ArmConstants.MC1;
  D46_tmp_h = rtP_ArmConstants.MC2 * rtP_ArmConstants.MC2;
  D46_tmp_i = rtP_ArmConstants.l1_dim * rtP_ArmConstants.l1_dim;
  D46_tmp_tmp_f = D46_tmp_d * rtP_ArmConstants.l1_dim;
  D46_tmp_j = D46_tmp_tmp_f * rtP_ArmConstants.Mass2;
  D46_tmp_tmp_f = 2.0 * rtP_ArmConstants.MC1;
  D46_tmp_k = D46_tmp_tmp_f * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  D46_tmp_tmp_5 = 2.0 * rtP_ArmConstants.Hexa_to_joint_L;
  D46_tmp_l = D46_tmp_tmp_5 * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  D46_tmp_m = D46_tmp_d * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  D46_tmp_tmp_4 = rtP_ArmConstants.Inertia2[6] * D46_tmp_4;
  D46_tmp_n = ((-rtP_ArmConstants.Inertia1[6] * D46_tmp_1 -
                rtP_ArmConstants.Inertia2[6] * D46_tmp_2) -
               rtP_ArmConstants.Inertia1[6] * D46_tmp_3) - D46_tmp_tmp_4;
  D46_tmp_o = rtP_ArmConstants.Inertia1[7] * D46_tmp_5;
  D46_tmp_p = D46_tmp_j * D46_tmp_9;
  D46_tmp_q = rtP_ArmConstants.Inertia2[7] * D46_tmp_6;
  D46_tmp_r = -2.0 * rtP_ArmConstants.Inertia1[8];
  D46_tmp_s = -2.0 * rtP_ArmConstants.Inertia2[8];
  D46_tmp_tmp_c = D46_tmp_g * -2.0;
  D46_tmp_t = D46_tmp_tmp_c * rtP_ArmConstants.Mass1;
  D46_tmp_tmp_d = D46_tmp_h * -2.0;
  D46_tmp_u = D46_tmp_tmp_d * rtP_ArmConstants.Mass2;
  D46_tmp_v = D46_tmp_i * -2.0 * rtP_ArmConstants.Mass2;
  D46_tmp_w = rtP_ArmConstants.Inertia1[7] * D46_tmp_7;
  D46_tmp_tmp_e = D46_tmp_f * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  D46_tmp_x = D46_tmp_tmp_e * D46_tmp_b;
  D46_tmp_y = rtP_ArmConstants.Inertia2[7] * D46_tmp_8;
  D46_tmp_z = -2.0 * rtP_ArmConstants.MC1;
  D46_tmp_10 = D46_tmp_z * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  D46_tmp_11 = -2.0 * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim
    * rtP_ArmConstants.Mass2;
  D46_tmp_12 = D46_tmp_f * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  D46_tmp_e = ((((((((((((((((((((D46_tmp_k * D46_tmp + D46_tmp_n) + D46_tmp_l *
    D46_tmp) + D46_tmp_o) + D46_tmp_p) + D46_tmp_m * D46_tmp_a) + D46_tmp_q) +
    D46_tmp_r * std::sin(rtu_InBus1_Positions[4])) + D46_tmp_s * std::sin
    (rtu_InBus1_Positions[4])) + -2.0 * rtP_HexaConstants.Inertia[0] * std::sin
    (rtu_InBus1_Positions[4])) + D46_tmp_t * std::sin(rtu_InBus1_Positions[4]))
                        + D46_tmp_e * rtP_ArmConstants.Mass1 * std::sin
                        (rtu_InBus1_Positions[4])) + D46_tmp_u * std::sin
                       (rtu_InBus1_Positions[4])) + D46_tmp_e *
                      rtP_ArmConstants.Mass2 * std::sin(rtu_InBus1_Positions[4]))
                     + D46_tmp_v * std::sin(rtu_InBus1_Positions[4])) +
                    D46_tmp_10 * D46_tmp_0) + D46_tmp_11 * D46_tmp_0) +
                  D46_tmp_w) + D46_tmp_x) + D46_tmp_12 * D46_tmp_c) + D46_tmp_y)
    * 0.5;

  /* 'DMatrix:126' D47=H1zz+H2zz+c1^2*ml1+c2^2*ml2+l1^2*ml2+L*(c1*ml1+l1*ml2)*cos(q1) ... */
  /* 'DMatrix:127'   +2*c2*l1*ml2*cos(q2)+c2*L*ml2*cos(q1+q2); */
  D47_tmp = D46_tmp_h * rtP_ArmConstants.Mass2;
  D47_tmp_tmp_tmp = rtP_ArmConstants.MC2 * rtP_ArmConstants.Hexa_to_joint_L;
  D47_tmp_tmp_tmp *= rtP_ArmConstants.Mass2;
  D47_tmp_0 = D47_tmp_tmp_tmp * s;
  D47_tmp_1 = D46_tmp_g * rtP_ArmConstants.Mass1;
  D47_tmp_2 = D46_tmp_i * rtP_ArmConstants.Mass2;
  D47_tmp_3 = rtP_ArmConstants.Inertia1[8] + rtP_ArmConstants.Inertia2[8];
  D47_tmp_4 = ((D47_tmp_1 + D47_tmp_3) + D47_tmp) + D47_tmp_2;
  D47_tmp_5 = D14_tmp_0 * rtP_ArmConstants.Hexa_to_joint_L;
  D47 = ((D47_tmp_5 * std::cos(rtu_InBus1_Positions[6]) + D47_tmp_4) + D46_tmp_j
         * std::cos(rtu_InBus1_Positions[7])) + D47_tmp_0;

  /* 'DMatrix:128' D48=H2zz+c2^2*ml2+c2*l1*ml2*cos(q2)+c2*L*ml2*cos(q1+q2); */
  D48_tmp = rtP_ArmConstants.MC2 * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  D48_tmp_0 = D47_tmp + rtP_ArmConstants.Inertia2[8];
  D48 = (D48_tmp * std::cos(rtu_InBus1_Positions[7]) + D48_tmp_0) + D47_tmp_0;

  /* 'DMatrix:35' [D55, D56, D57, D58] = get_D5(); */
  /* 'DMatrix:132' D55=(1/2)*(H1xx+H1yy+H2xx+H2yy+Hby+Hbz+c1^2*ml1+L^2*ml1+c2^2*ml2+ ... */
  /* 'DMatrix:133'   L^2*ml2+l1^2*ml2+Hby*cos(2*phi)-Hbz*cos(2*phi)+L^2*ml1* ... */
  /* 'DMatrix:134'   cos(2*phi)+L^2*ml2*cos(2*phi)+2*L*(c1*ml1+l1*ml2)*cos(q1)+(-1) ... */
  /* 'DMatrix:135'   *H1xx*cos(2*(phi+q1))+H1yy*cos(2*(phi+q1))+c1^2*ml1*cos(2*(phi+ ... */
  /* 'DMatrix:136'   q1))+l1^2*ml2*cos(2*(phi+q1))+2*c1*L*ml1*cos(2*phi+q1)+2*L* ... */
  /* 'DMatrix:137'   l1*ml2*cos(2*phi+q1)+2*c2*l1*ml2*cos(q2)+2*c2*L*ml2*cos(q1+ ... */
  /* 'DMatrix:138'   q2)-H2xx*cos(2*(phi+q1+q2))+H2yy*cos(2*(phi+q1+q2))+c2^2* ... */
  /* 'DMatrix:139'   ml2*cos(2*(phi+q1+q2))+2*c2*L*ml2*cos(2*phi+q1+q2)+2*c2*l1* ... */
  /* 'DMatrix:140'   ml2*cos(2*(phi+q1)+q2)+2*H1xy*sin(2*(phi+q1))+2*H2xy*sin(2*(phi+ ... */
  /* 'DMatrix:141'   q1+q2))); */
  /* 'DMatrix:142' D56=(1/4)*((-2)*H1zx*cos(phi+q1-th)+(-2)*H1xy*cos(2*phi+2*q1+( ... */
  /* 'DMatrix:143'   -1)*th)+(-2)*H2zx*cos(phi+q1+q2-th)+(-2)*H2xy*cos(2*phi+2* ... */
  /* 'DMatrix:144'   q1+2*q2-th)+2*H1zx*cos(phi+q1+th)+(-2)*H1xy*cos(2*phi+2*q1+ ... */
  /* 'DMatrix:145'   th)+2*H2zx*cos(phi+q1+q2+th)+(-2)*H2xy*cos(2*phi+2*q1+2*q2+th)+ ... */
  /* 'DMatrix:146'   Hby*sin(2*phi-th)-Hbz*sin(2*phi-th)+L^2*ml1* ... */
  /* 'DMatrix:147'   sin(2*phi-th)+L^2*ml2*sin(2*phi-th)+2*H1yz*sin(phi+ ... */
  /* 'DMatrix:148'   q1-th)+2*c1*L*ml1*sin(2*phi+q1-th)+2*L*l1*ml2*sin( ... */
  /* 'DMatrix:149'   2*phi+q1-th)-H1xx*sin(2*phi+2*q1-th)+H1yy*sin(2* ... */
  /* 'DMatrix:150'   phi+2*q1-th)+c1^2*ml1*sin(2*phi+2*q1-th)+l1^2*ml2* ... */
  /* 'DMatrix:151'   sin(2*phi+2*q1-th)+2*H2yz*sin(phi+q1+q2-th)+2*c2*L* ... */
  /* 'DMatrix:152'   ml2*sin(2*phi+q1+q2-th)+2*c2*l1*ml2*sin(2*phi+2*q1+q2+(-1) ... */
  /* 'DMatrix:153'   *th)-H2xx*sin(2*phi+2*q1+2*q2-th)+H2yy*sin(2*phi+2* ... */
  /* 'DMatrix:154'   q1+2*q2-th)+c2^2*ml2*sin(2*phi+2*q1+2*q2-th)+Hby* ... */
  /* 'DMatrix:155'   sin(2*phi+th)-Hbz*sin(2*phi+th)+L^2*ml1*sin(2*phi+th)+ ... */
  /* 'DMatrix:156'   L^2*ml2*sin(2*phi+th)+(-2)*H1yz*sin(phi+q1+th)+2*c1*L*ml1*sin( ... */
  /* 'DMatrix:157'   2*phi+q1+th)+2*L*l1*ml2*sin(2*phi+q1+th)-H1xx*sin(2*phi+ ... */
  /* 'DMatrix:158'   2*q1+th)+H1yy*sin(2*phi+2*q1+th)+c1^2*ml1*sin(2*phi+2*q1+th)+ ... */
  /* 'DMatrix:159'   l1^2*ml2*sin(2*phi+2*q1+th)+(-2)*H2yz*sin(phi+q1+q2+th)+2*c2* ... */
  /* 'DMatrix:160'   L*ml2*sin(2*phi+q1+q2+th)+2*c2*l1*ml2*sin(2*phi+2*q1+q2+th)+( ... */
  /* 'DMatrix:161'   -1)*H2xx*sin(2*phi+2*q1+2*q2+th)+H2yy*sin(2*phi+2*q1+2*q2+th)+ ... */
  /* 'DMatrix:162'   c2^2*ml2*sin(2*phi+2*q1+2*q2+th)); */
  D56_tmp_tmp = 2.0 * rtu_InBus1_Positions[3];
  D56_tmp_tmp_9 = D56_tmp_tmp - rtu_InBus1_Positions[4];
  D56_tmp = std::sin(D56_tmp_tmp_9);
  D56_tmp_tmp_1 = D56_tmp_tmp + rtu_InBus1_Positions[6];
  D56_tmp_tmp_6 = D56_tmp_tmp_1 - rtu_InBus1_Positions[4];
  D56_tmp_0 = std::sin(D56_tmp_tmp_6);
  D56_tmp_tmp_tmp = 2.0 * rtu_InBus1_Positions[6];
  D56_tmp_tmp_0 = D56_tmp_tmp + D56_tmp_tmp_tmp;
  D56_tmp_tmp_3 = D56_tmp_tmp_0 - rtu_InBus1_Positions[4];
  D56_tmp_1 = std::sin(D56_tmp_tmp_3);
  D56_tmp_tmp_2 = 2.0 * rtu_InBus1_Positions[7] + D56_tmp_tmp_0;
  D56_tmp_tmp_4 = D56_tmp_tmp_2 - rtu_InBus1_Positions[4];
  D56_tmp_2 = std::sin(D56_tmp_tmp_4);
  D56_tmp_tmp_7 = D56_tmp_tmp + rtu_InBus1_Positions[4];
  D56_tmp_3 = std::sin(D56_tmp_tmp_7);
  D56_tmp_tmp_8 = D56_tmp_tmp_1 + rtu_InBus1_Positions[4];
  D56_tmp_4 = std::sin(D56_tmp_tmp_8);
  D56_tmp_tmp_5 = D56_tmp_tmp_0 + rtu_InBus1_Positions[4];
  D56_tmp_5 = std::sin(D56_tmp_tmp_5);
  D56_tmp_tmp_2 += rtu_InBus1_Positions[4];
  D56_tmp_6 = std::sin(D56_tmp_tmp_2);
  D56_tmp_7 = std::cos(D56_tmp_tmp_3);
  D56_tmp_8 = std::cos(D56_tmp_tmp_4);
  D56_tmp_9 = std::cos(D56_tmp_tmp_5);
  D56_tmp_a = std::cos(D56_tmp_tmp_2);
  D56_tmp_tmp_3 = D56_tmp_tmp_1 + rtu_InBus1_Positions[7];
  D56_tmp_tmp_2 = D56_tmp_tmp_3 - rtu_InBus1_Positions[4];
  D56_tmp_b = std::sin(D56_tmp_tmp_2);
  D56_tmp_tmp_0 += rtu_InBus1_Positions[7];
  D56_tmp_tmp_4 = D56_tmp_tmp_0 - rtu_InBus1_Positions[4];
  D56_tmp_c = std::sin(D56_tmp_tmp_4);
  D56_tmp_tmp_5 = D56_tmp_tmp_3 + rtu_InBus1_Positions[4];
  D56_tmp_d = std::sin(D56_tmp_tmp_5);
  D56_tmp_tmp_0 += rtu_InBus1_Positions[4];
  D56_tmp_e = std::sin(D56_tmp_tmp_0);
  D56_tmp_f = -2.0 * rtP_ArmConstants.Inertia1[3];
  D56_tmp_g = -2.0 * rtP_ArmConstants.Inertia2[3];
  D56_tmp_h = D46_tmp_tmp_3 * rtP_ArmConstants.Mass1;
  D56_tmp_i = D46_tmp_tmp_3 * rtP_ArmConstants.Mass2;
  D56_tmp_j = 2.0 * rtP_ArmConstants.Inertia1[7];
  D56_tmp_k = 2.0 * rtP_ArmConstants.Inertia2[7];
  D56_tmp_l = -2.0 * rtP_ArmConstants.Inertia1[7];
  D56_tmp_m = -2.0 * rtP_ArmConstants.Inertia2[7];
  D56_tmp_n = 2.0 * rtP_ArmConstants.Inertia1[6];
  D56_tmp_o = 2.0 * rtP_ArmConstants.Inertia2[6];
  D56_tmp_p = -2.0 * rtP_ArmConstants.Inertia1[6];
  D56_tmp_q = -2.0 * rtP_ArmConstants.Inertia2[6];
  D56_tmp_r = D56_tmp_p * D46_tmp_1 + D56_tmp_f * D56_tmp_7;
  D56_tmp_s = D56_tmp_q * D46_tmp_2;
  D56_tmp_tmp_a = rtP_HexaConstants.Inertia[4] * D56_tmp;
  D56_tmp_tmp_b = rtP_HexaConstants.Inertia[8] * D56_tmp;
  D56_tmp_tmp_c = D56_tmp_h * D56_tmp;
  D56_tmp_tmp_d = D56_tmp_i * D56_tmp;
  D56_tmp_tmp_e = rtP_ArmConstants.Inertia1[0] * D56_tmp_1;
  D56_tmp_tmp_f = rtP_ArmConstants.Inertia1[4] * D56_tmp_1;
  D56_tmp_tmp_g = D47_tmp_1 * D56_tmp_1;
  D56_tmp_tmp_h = D47_tmp_2 * D56_tmp_1;
  D56_tmp_tmp_i = rtP_ArmConstants.Inertia2[0] * D56_tmp_2;
  D56_tmp_tmp_j = rtP_ArmConstants.Inertia2[4] * D56_tmp_2;
  D56_tmp_tmp_k = D47_tmp * D56_tmp_2;
  D56_tmp_tmp_l = rtP_HexaConstants.Inertia[4] * D56_tmp_3;
  D56_tmp_tmp_m = rtP_HexaConstants.Inertia[8] * D56_tmp_3;
  D56_tmp_tmp_n = D56_tmp_h * D56_tmp_3;
  D56_tmp_tmp_o = rtP_ArmConstants.Inertia1[0] * D56_tmp_5;
  D56_tmp_tmp_p = rtP_ArmConstants.Inertia1[4] * D56_tmp_5;
  D56_tmp_tmp_q = D47_tmp_1 * D56_tmp_5;
  D56_tmp_tmp_r = D47_tmp_2 * D56_tmp_5;
  D56_tmp = ((((((((((((((((((((((((((((((((((((D56_tmp_r + D56_tmp_s) +
    D56_tmp_g * D56_tmp_8) + D56_tmp_n * D46_tmp_3) + D56_tmp_f * D56_tmp_9) +
    D56_tmp_o * D46_tmp_4) + D56_tmp_g * D56_tmp_a) + D56_tmp_tmp_a) -
    D56_tmp_tmp_b) + D56_tmp_tmp_c) + D56_tmp_tmp_d) + D56_tmp_j * D46_tmp_5) +
    D46_tmp_k * D56_tmp_0) + D46_tmp_l * D56_tmp_0) - D56_tmp_tmp_e) +
    D56_tmp_tmp_f) + D56_tmp_tmp_g) + D56_tmp_tmp_h) + D56_tmp_k * D46_tmp_6) +
    D46_tmp_m * D56_tmp_b) + D46_tmp_j * D56_tmp_c) - D56_tmp_tmp_i) +
    D56_tmp_tmp_j) + D56_tmp_tmp_k) + D56_tmp_tmp_l) - D56_tmp_tmp_m) +
                       D56_tmp_tmp_n) + D56_tmp_i * D56_tmp_3) + D56_tmp_l *
                     D46_tmp_7) + D46_tmp_k * D56_tmp_4) + D46_tmp_l * D56_tmp_4)
                  - D56_tmp_tmp_o) + D56_tmp_tmp_p) + D56_tmp_tmp_q) +
               D56_tmp_tmp_r) + D56_tmp_m * D46_tmp_8) + D46_tmp_m * D56_tmp_d)
    + D46_tmp_j * D56_tmp_e;
  D56_tmp_r = rtP_ArmConstants.Inertia2[4] * D56_tmp_6;
  D56_tmp_s = D47_tmp * D56_tmp_6;
  D56 = (((-rtP_ArmConstants.Inertia2[0] * D56_tmp_6 + D56_tmp) + D56_tmp_r) +
         D56_tmp_s) * 0.25;

  /* 'DMatrix:163' D57=H1yz*cos(phi+q1)+H2yz*cos(phi+q1+q2)+H1zx*sin(phi+q1)+H2zx*sin(phi+ ... */
  /* 'DMatrix:164'   q1+q2); */
  D57 = D45;

  /* 'DMatrix:165' D58=H2yz*cos(phi+q1+q2)+H2zx*sin(phi+q1+q2); */
  D45_tmp += D45_tmp_0;

  /* 'DMatrix:36' [D66, D67, D68] = get_D6(); */
  /* 'DMatrix:169' D66=Hbz*cos(phi)^2*cos(th)^2+Hby*cos(th)^2*sin(phi)^2+2*cos(phi)* ... */
  /* 'DMatrix:170'   cos(th)^2*sin(phi)*(-H1xy*cos(2*q1)+(-H1xx+H1yy)*cos(q1) ... */
  /* 'DMatrix:171'   *sin(q1))+cos(phi)^2*cos(th)^2*(H1xx*cos(q1)^2+H1yy*sin(q1)^2+( ... */
  /* 'DMatrix:172'   -1)*H1xy*sin(2*q1))+cos(th)^2*sin(phi)^2*(H1yy*cos(q1)^2+H1xx* ... */
  /* 'DMatrix:173'   sin(q1)^2+H1xy*sin(2*q1))+(1/2)*cos(phi)^2*cos(th)^2*(H2xx+H2yy+ ... */
  /* 'DMatrix:174'   (H2xx-H2yy)*cos(2*(q1+q2))+(-2)*H2xy*sin(2*(q1+q2)))+(1/2)* ... */
  /* 'DMatrix:175'   cos(th)^2*sin(phi)^2*(H2xx+H2yy+(-H2xx+H2yy)*cos(2*(q1+q2))+ ... */
  /* 'DMatrix:176'   2*H2xy*sin(2*(q1+q2)))+2*cos(phi)*cos(th)^2*sin(phi)*(- ... */
  /* 'DMatrix:177'   H2xy*cos(2*(q1+q2))+(1/2)*(-H2xx+H2yy)*sin(2*(q1+q2)))+H1zz* ... */
  /* 'DMatrix:178'   sin(th)^2+H2zz*sin(th)^2+Hbx*sin(th)^2+ml1*(-(L+c1*cos(q1)) ... */
  /* 'DMatrix:179'   *(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))+c1*sin(q1)*(- ... */
  /* 'DMatrix:180'   cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th)))^2+ml2*(-(L+l1* ... */
  /* 'DMatrix:181'   cos(q1)+c2*cos(q1+q2))*(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th) ... */
  /* 'DMatrix:182'   )+(l1*sin(q1)+c2*sin(q1+q2))*(-cos(phi)*sin(psi)+cos(psi)*sin( ... */
  /* 'DMatrix:183'   phi)*sin(th)))^2+ml1*((L+c1*cos(q1))*(cos(psi)*sin(phi)-cos( ... */
  /* 'DMatrix:184'   phi)*sin(psi)*sin(th))+c1*sin(q1)*(cos(phi)*cos(psi)+sin(phi)*sin( ... */
  /* 'DMatrix:185'   psi)*sin(th)))^2+ml2*((L+l1*cos(q1)+c2*cos(q1+q2))*(cos(psi)*sin( ... */
  /* 'DMatrix:186'   phi)-cos(phi)*sin(psi)*sin(th))+(l1*sin(q1)+c2*sin(q1+q2))*( ... */
  /* 'DMatrix:187'   cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th)))^2+cos(phi)*(H1zx* ... */
  /* 'DMatrix:188'   cos(q1)-H1yz*sin(q1))*sin(2*th)-sin(phi)*(H1yz*cos(q1)+ ... */
  /* 'DMatrix:189'   H1zx*sin(q1))*sin(2*th)+cos(phi)*(H2zx*cos(q1+q2)-H2yz*sin( ... */
  /* 'DMatrix:190'   q1+q2))*sin(2*th)-sin(phi)*(H2yz*cos(q1+q2)+H2zx*sin(q1+q2)) ... */
  /* 'DMatrix:191'   *sin(2*th); */
  D45_tmp_0 = std::cos(rtu_InBus1_Positions[3]);
  c_a = std::cos(rtu_InBus1_Positions[4]);
  d_a = std::cos(rtu_InBus1_Positions[4]);
  e_a = std::sin(rtu_InBus1_Positions[3]);
  f_a = std::cos(rtu_InBus1_Positions[4]);
  g_a = std::cos(rtu_InBus1_Positions[3]);
  h_a = std::cos(rtu_InBus1_Positions[4]);
  i_a = std::cos(rtu_InBus1_Positions[6]);
  j_a = std::sin(rtu_InBus1_Positions[6]);
  k_a = std::cos(rtu_InBus1_Positions[4]);
  l_a = std::sin(rtu_InBus1_Positions[3]);
  m_a = std::cos(rtu_InBus1_Positions[6]);
  n_a = std::sin(rtu_InBus1_Positions[6]);
  o_a = std::cos(rtu_InBus1_Positions[3]);
  p_a = std::cos(rtu_InBus1_Positions[4]);
  q_a = std::cos(rtu_InBus1_Positions[4]);
  r_a = std::sin(rtu_InBus1_Positions[3]);
  s_a = std::cos(rtu_InBus1_Positions[4]);
  t_a = std::sin(rtu_InBus1_Positions[4]);
  u_a = std::sin(rtu_InBus1_Positions[4]);
  v_a = std::sin(rtu_InBus1_Positions[4]);
  w_a = (std::cos(rtu_InBus1_Positions[3]) * std::cos(rtu_InBus1_Positions[5]) *
         std::sin(rtu_InBus1_Positions[4]) + std::sin(rtu_InBus1_Positions[3]) *
         std::sin(rtu_InBus1_Positions[5])) * -(rtP_ArmConstants.MC1 * std::cos
    (rtu_InBus1_Positions[6]) + rtP_ArmConstants.Hexa_to_joint_L) + (std::cos
    (rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[3]) * std::sin
    (rtu_InBus1_Positions[4]) + -std::cos(rtu_InBus1_Positions[3]) * std::sin
    (rtu_InBus1_Positions[5])) * (rtP_ArmConstants.MC1 * std::sin
    (rtu_InBus1_Positions[6]));
  x_a = -((rtP_ArmConstants.l1_dim * std::cos(rtu_InBus1_Positions[6]) +
           rtP_ArmConstants.Hexa_to_joint_L) + D17_tmp_0) * (std::cos
    (rtu_InBus1_Positions[3]) * std::cos(rtu_InBus1_Positions[5]) * std::sin
    (rtu_InBus1_Positions[4]) + std::sin(rtu_InBus1_Positions[3]) * std::sin
    (rtu_InBus1_Positions[5])) + (std::cos(rtu_InBus1_Positions[5]) * std::sin
    (rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[4]) + -std::cos
    (rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5])) *
    (rtP_ArmConstants.l1_dim * std::sin(rtu_InBus1_Positions[6]) + D17_tmp);
  y_a = (std::cos(rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[3]) -
         std::cos(rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5]) *
         std::sin(rtu_InBus1_Positions[4])) * (rtP_ArmConstants.MC1 * std::cos
    (rtu_InBus1_Positions[6]) + rtP_ArmConstants.Hexa_to_joint_L) + (std::sin
    (rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5]) * std::sin
    (rtu_InBus1_Positions[4]) + std::cos(rtu_InBus1_Positions[3]) * std::cos
    (rtu_InBus1_Positions[5])) * (rtP_ArmConstants.MC1 * std::sin
    (rtu_InBus1_Positions[6]));
  ab_a = ((rtP_ArmConstants.l1_dim * std::cos(rtu_InBus1_Positions[6]) +
           rtP_ArmConstants.Hexa_to_joint_L) + D17_tmp_0) * (std::cos
    (rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[3]) - std::cos
    (rtu_InBus1_Positions[3]) * std::sin(rtu_InBus1_Positions[5]) * std::sin
    (rtu_InBus1_Positions[4])) + (std::sin(rtu_InBus1_Positions[3]) * std::sin
    (rtu_InBus1_Positions[5]) * std::sin(rtu_InBus1_Positions[4]) + std::cos
    (rtu_InBus1_Positions[3]) * std::cos(rtu_InBus1_Positions[5])) *
    (rtP_ArmConstants.l1_dim * std::sin(rtu_InBus1_Positions[6]) + D17_tmp);

  /* 'DMatrix:192' D67=(1/2)*(-H1zx*cos(phi+q1-th)-H2zx*cos(phi+q1+q2+(-1) ... */
  /* 'DMatrix:193'   *th)-H1zx*cos(phi+q1+th)-H2zx*cos(phi+q1+q2+th)+c1*L* ... */
  /* 'DMatrix:194'   ml1*sin(q1-th)+L*l1*ml2*sin(q1-th)+H1yz*sin(phi+q1+(-1) ... */
  /* 'DMatrix:195'   *th)+2*c2*l1*ml2*sin(q2-th)+c2*L*ml2*sin(q1+q2-th)+ ... */
  /* 'DMatrix:196'   H2yz*sin(phi+q1+q2-th)+(-2)*H1zz*sin(th)+(-2)*H2zz*sin(th)+( ... */
  /* 'DMatrix:197'   -2)*c1^2*ml1*sin(th)+(-2)*c2^2*ml2*sin(th)+(-2)*l1^2*ml2* ... */
  /* 'DMatrix:198'   sin(th)-c1*L*ml1*sin(q1+th)-L*l1*ml2*sin(q1+th)+H1yz* ... */
  /* 'DMatrix:199'   sin(phi+q1+th)+(-2)*c2*l1*ml2*sin(q2+th)-c2*L*ml2*sin(q1+ ... */
  /* 'DMatrix:200'   q2+th)+H2yz*sin(phi+q1+q2+th)); */
  D67_tmp = rtP_ArmConstants.MC1 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  D67_tmp_0 = rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  D46_tmp_a *= D47_tmp_tmp_tmp;
  D46_tmp_c *= D47_tmp_tmp_tmp;
  D46_tmp_n = (((((((((((((((((D67_tmp * D46_tmp + D46_tmp_n) + D67_tmp_0 *
    D46_tmp) + D46_tmp_o) + D46_tmp_p) + D46_tmp_a) + D46_tmp_q) + D46_tmp_r *
    std::sin(rtu_InBus1_Positions[4])) + D46_tmp_s * std::sin
                        (rtu_InBus1_Positions[4])) + D46_tmp_t * std::sin
                       (rtu_InBus1_Positions[4])) + D46_tmp_u * std::sin
                      (rtu_InBus1_Positions[4])) + D46_tmp_v * std::sin
                     (rtu_InBus1_Positions[4])) - D67_tmp * D46_tmp_0) -
                   D67_tmp_0 * D46_tmp_0) + D46_tmp_w) + D46_tmp_x) - D46_tmp_c)
               + D46_tmp_y) * 0.5;

  /* 'DMatrix:201' D68=(1/2)*(-H2zx*cos(phi+q1+q2-th)-H2zx*cos(phi+q1+q2+ ... */
  /* 'DMatrix:202'   th)+c2*l1*ml2*sin(q2-th)+c2*L*ml2*sin(q1+q2-th)+H2yz* ... */
  /* 'DMatrix:203'   sin(phi+q1+q2-th)+(-2)*H2zz*sin(th)+(-2)*c2^2*ml2*sin(th)+( ... */
  /* 'DMatrix:204'   -1)*c2*l1*ml2*sin(q2+th)-c2*L*ml2*sin(q1+q2+th)+H2yz*sin( ... */
  /* 'DMatrix:205'   phi+q1+q2+th)); */
  D46_tmp_o = -rtP_ArmConstants.MC2 * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  D46_tmp_q = (((((((((-rtP_ArmConstants.Inertia2[6] * D46_tmp_2 - D46_tmp_tmp_4)
                      + D48_tmp * D46_tmp_9) + D46_tmp_a) + D46_tmp_q) +
                   D46_tmp_s * std::sin(rtu_InBus1_Positions[4])) + D46_tmp_u *
                  std::sin(rtu_InBus1_Positions[4])) + D46_tmp_o * D46_tmp_b) -
                D46_tmp_c) + D46_tmp_y) * 0.5;

  /* 'DMatrix:37' [D77, D78] = get_D7(); */
  /* 'DMatrix:209' D77=H1zz+H2zz+c1^2*ml1+c2^2*ml2+l1^2*ml2+2*c2*l1*ml2*cos(q2); */
  /* 'DMatrix:210' D78=H2zz+c2^2*ml2+c2*l1*ml2*cos(q2); */
  D46_tmp_s = D48_tmp * std::cos(rtu_InBus1_Positions[7]) + D48_tmp_0;

  /* 'DMatrix:38' D88=H2zz+c2^2*ml2; */
  /* 'DMatrix:40' DM = [D11, D12, D13, D14, D15, D16, D17, D18;... */
  /* 'DMatrix:41'       D12, D22, D23, D24, D25, D26, D27, D28;... */
  /* 'DMatrix:42'       D13, D23, D33, D34, D35, D36, D37, D38;... */
  /* 'DMatrix:43'       D14, D24, D34, D44, D45, D46, D47, D48;... */
  /* 'DMatrix:44'       D15, D25, D35, D45, D55, D56, D57, D58;... */
  /* 'DMatrix:45'       D16, D26, D36, D46, D56, D66, D67, D68;... */
  /* 'DMatrix:46'       D17, D27, D37, D47, D57, D67, D77, D78;... */
  /* 'DMatrix:47'       D18, D28, D38, D48, D58, D68, D78, D88]; */
  D46_tmp_9 = std::cos(D56_tmp_tmp);
  D46_tmp_tmp_4 = D15_tmp_tmp * 2.0;
  D46_tmp_a = std::cos(D46_tmp_tmp_4);
  D46_tmp_b = std::cos(D56_tmp_tmp_1);
  D46_tmp_r = D15_tmp_tmp_0 * 2.0;
  D46_tmp_c = std::cos(D46_tmp_r);
  D46_tmp = std::sin(D56_tmp_tmp_tmp);
  D46_tmp_u = smax_tmp * 2.0;
  D46_tmp_0 = std::cos(D46_tmp_u);
  D46_tmp_u = std::sin(D46_tmp_u);
  ginv_tmp_tmp_0 = 2.0 * rtu_InBus1_Positions[4];
  D46_tmp_y = std::sin(ginv_tmp_tmp_0);
  D46_tmp_p = std::sin(D46_tmp_tmp_4);
  D46_tmp_r = std::sin(D46_tmp_r);
  D46_tmp_t = std::cos(D56_tmp_tmp_3);
  ginv_tmp_tmp = D46_tmp_tmp_4 + rtu_InBus1_Positions[7];
  D46_tmp_tmp_4 = std::cos(ginv_tmp_tmp);
  D56_tmp_tmp_tmp = std::cos(D56_tmp_tmp_tmp);
  D46_tmp_v = std::cos(rtu_InBus1_Positions[6]);
  D46_tmp_w = std::cos(rtu_InBus1_Positions[7]);
  D46_tmp_x = std::cos(rtu_InBus1_Positions[6]);
  tmp = std::cos(rtu_InBus1_Positions[7]);
  tmp_0 = std::cos(rtu_InBus1_Positions[3]);
  tmp_1 = std::sin(rtu_InBus1_Positions[3]);
  tmp_2 = std::cos(rtu_InBus1_Positions[6]);
  tmp_3 = std::sin(rtu_InBus1_Positions[6]);
  tmp_4 = std::cos(rtu_InBus1_Positions[3]);
  tmp_5 = std::sin(rtu_InBus1_Positions[3]);
  tmp_6 = std::cos(rtu_InBus1_Positions[3]);
  tmp_7 = std::cos(rtu_InBus1_Positions[6]);
  tmp_8 = std::sin(rtu_InBus1_Positions[6]);
  tmp_9 = std::sin(rtu_InBus1_Positions[3]);
  tmp_a = std::cos(rtu_InBus1_Positions[6]);
  tmp_b = std::sin(rtu_InBus1_Positions[6]);
  tmp_c = std::cos(rtu_InBus1_Positions[3]);
  tmp_d = std::sin(rtu_InBus1_Positions[3]);
  tmp_e = std::cos(rtu_InBus1_Positions[7]);
  ginv_tmp = (rtP_HexaConstants.Mass + rtP_ArmConstants.Mass1) +
    rtP_ArmConstants.Mass2;
  PD_B.ginv[0] = ginv_tmp;
  PD_B.ginv[8] = 0.0;
  PD_B.ginv[16] = 0.0;
  PD_B.ginv[24] = D14;
  PD_B.ginv[32] = D15;
  PD_B.ginv[40] = D16;
  PD_B.ginv[48] = D17;
  PD_B.ginv[56] = D18;
  PD_B.ginv[1] = 0.0;
  PD_B.ginv[9] = ginv_tmp;
  PD_B.ginv[17] = 0.0;
  PD_B.ginv[25] = D24;
  PD_B.ginv[33] = D25;
  PD_B.ginv[41] = D14_tmp_tmp;
  PD_B.ginv[49] = D27;
  PD_B.ginv[57] = D28;
  PD_B.ginv[2] = 0.0;
  PD_B.ginv[10] = 0.0;
  PD_B.ginv[18] = ginv_tmp;
  PD_B.ginv[26] = D34;
  PD_B.ginv[34] = D35;
  PD_B.ginv[42] = 0.0;
  PD_B.ginv[50] = D37;
  PD_B.ginv[58] = D38;
  PD_B.ginv[3] = D14;
  PD_B.ginv[11] = D24;
  PD_B.ginv[19] = D34;
  ginv_tmp_0 = D14_tmp_0 * D46_tmp_tmp_5;
  ginv_tmp_1 = D46_tmp_m * s;
  D47_tmp_3 = (((((D47_tmp_3 + rtP_HexaConstants.Inertia[0]) + D47_tmp_1) +
                 D56_tmp_h) + D47_tmp) + D56_tmp_i) + D47_tmp_2;
  PD_B.ginv[27] = ((ginv_tmp_0 * D46_tmp_v + D47_tmp_3) + D46_tmp_j * D46_tmp_w)
    + ginv_tmp_1;
  PD_B.ginv[35] = D45;
  PD_B.ginv[43] = D46_tmp_e;
  PD_B.ginv[51] = D47;
  PD_B.ginv[59] = D48;
  PD_B.ginv[4] = D15;
  PD_B.ginv[12] = D25;
  PD_B.ginv[20] = D35;
  PD_B.ginv[28] = D45;
  ginv_tmp_3 = 2.0 * rtP_ArmConstants.Inertia2[3];
  ginv_tmp_5 = 2.0 * rtP_ArmConstants.Inertia1[3];
  ginv_tmp_6 = rtP_ArmConstants.Inertia1[4] * D46_tmp_a;
  ginv_tmp_7 = D47_tmp_1 * D46_tmp_a;
  ginv_tmp_8 = D47_tmp_2 * D46_tmp_a;
  ginv_tmp_9 = rtP_ArmConstants.Inertia2[0] * D46_tmp_c;
  ginv_tmp_a = rtP_ArmConstants.Inertia2[4] * D46_tmp_c;
  ginv_tmp_b = D47_tmp * D46_tmp_c;
  PD_B.ginv[36] = ((((((((((((((((((((((((((((((rtP_ArmConstants.Inertia1[0] +
    rtP_ArmConstants.Inertia1[4]) + rtP_ArmConstants.Inertia2[0]) +
    rtP_ArmConstants.Inertia2[4]) + rtP_HexaConstants.Inertia[4]) +
    rtP_HexaConstants.Inertia[8]) + D47_tmp_1) + D56_tmp_h) + D47_tmp) +
    D56_tmp_i) + D47_tmp_2) + rtP_HexaConstants.Inertia[4] * D46_tmp_9) -
    rtP_HexaConstants.Inertia[8] * D46_tmp_9) + D56_tmp_h * D46_tmp_9) +
    D56_tmp_i * D46_tmp_9) + ginv_tmp_0 * D46_tmp_x) +
    -rtP_ArmConstants.Inertia1[0] * D46_tmp_a) + ginv_tmp_6) + ginv_tmp_7) +
    ginv_tmp_8) + D46_tmp_k * D46_tmp_b) + D46_tmp_l * D46_tmp_b) + D46_tmp_j *
    tmp) + ginv_tmp_1) - ginv_tmp_9) + ginv_tmp_a) + ginv_tmp_b) + D46_tmp_m *
                      D46_tmp_t) + D46_tmp_j * D46_tmp_tmp_4) + ginv_tmp_5 *
                    D46_tmp_p) + ginv_tmp_3 * D46_tmp_r) * 0.5;
  PD_B.ginv[44] = D56;
  PD_B.ginv[52] = D57;
  PD_B.ginv[60] = D45_tmp;
  PD_B.ginv[5] = D16;
  PD_B.ginv[13] = D14_tmp_tmp;
  PD_B.ginv[21] = 0.0;
  PD_B.ginv[29] = D46_tmp_e;
  PD_B.ginv[37] = D56;
  ginv_tmp_2 = rtP_ArmConstants.Inertia2[0] + rtP_ArmConstants.Inertia2[4];
  ginv_tmp_4 = -rtP_ArmConstants.Inertia2[0] + rtP_ArmConstants.Inertia2[4];
  ginv_tmp_c = rtP_ArmConstants.Inertia2[6] * s - rtP_ArmConstants.Inertia2[7] *
    smax;
  ginv_tmp_d = rtP_ArmConstants.Inertia2[7] * s + rtP_ArmConstants.Inertia2[6] *
    smax;
  ginv_tmp_e = rtP_ArmConstants.Inertia1[3] * D46_tmp;
  ginv_tmp_tmp_1 = rtP_ArmConstants.Inertia2[0] - rtP_ArmConstants.Inertia2[4];
  ginv_tmp_f = (ginv_tmp_tmp_1 * D46_tmp_0 + ginv_tmp_2) + D56_tmp_g * D46_tmp_u;
  ginv_tmp_tmp_2 = ginv_tmp_4 * D46_tmp_0;
  ginv_tmp_tmp_3 = ginv_tmp_3 * D46_tmp_u;
  ginv_tmp_2 = (ginv_tmp_tmp_2 + ginv_tmp_2) + ginv_tmp_tmp_3;
  PD_B.ginv[45] = ((((((((((((((((((-rtP_ArmConstants.Inertia1[0] +
    rtP_ArmConstants.Inertia1[4]) * tmp_2 * tmp_3 + -rtP_ArmConstants.Inertia1[3]
    * D56_tmp_tmp_tmp) * (2.0 * tmp_0 * (f_a * f_a) * tmp_1) + (D45_tmp_0 *
    D45_tmp_0 * rtP_HexaConstants.Inertia[8] * (c_a * c_a) + d_a * d_a *
    rtP_HexaConstants.Inertia[4] * (e_a * e_a))) + ((i_a * i_a *
    rtP_ArmConstants.Inertia1[0] + j_a * j_a * rtP_ArmConstants.Inertia1[4]) +
    -rtP_ArmConstants.Inertia1[3] * D46_tmp) * (g_a * g_a * (h_a * h_a))) +
    ((m_a * m_a * rtP_ArmConstants.Inertia1[4] + n_a * n_a *
      rtP_ArmConstants.Inertia1[0]) + ginv_tmp_e) * (k_a * k_a * (l_a * l_a))) +
    o_a * o_a * 0.5 * (p_a * p_a) * ginv_tmp_f) + q_a * q_a * 0.5 * (r_a * r_a) *
    ginv_tmp_2) + (ginv_tmp_4 * 0.5 * D46_tmp_u + -rtP_ArmConstants.Inertia2[3] *
                   D46_tmp_0) * (2.0 * tmp_4 * (s_a * s_a) * tmp_5)) + t_a * t_a
    * rtP_ArmConstants.Inertia1[8]) + u_a * u_a * rtP_ArmConstants.Inertia2[8])
    + v_a * v_a * rtP_HexaConstants.Inertia[0]) + w_a * w_a *
    rtP_ArmConstants.Mass1) + x_a * x_a * rtP_ArmConstants.Mass2) + y_a * y_a *
                       rtP_ArmConstants.Mass1) + ab_a * ab_a *
                      rtP_ArmConstants.Mass2) + (rtP_ArmConstants.Inertia1[6] *
    tmp_7 - rtP_ArmConstants.Inertia1[7] * tmp_8) * tmp_6 * D46_tmp_y) -
                    (rtP_ArmConstants.Inertia1[7] * tmp_a +
                     rtP_ArmConstants.Inertia1[6] * tmp_b) * tmp_9 * D46_tmp_y)
                   + ginv_tmp_c * tmp_c * D46_tmp_y) - ginv_tmp_d * tmp_d *
    D46_tmp_y;
  PD_B.ginv[53] = D46_tmp_n;
  PD_B.ginv[61] = D46_tmp_q;
  PD_B.ginv[6] = D17;
  PD_B.ginv[14] = D27;
  PD_B.ginv[22] = D37;
  PD_B.ginv[30] = D47;
  PD_B.ginv[38] = D57;
  PD_B.ginv[46] = D46_tmp_n;
  PD_B.ginv[54] = D46_tmp_j * tmp_e + D47_tmp_4;
  PD_B.ginv[62] = D46_tmp_s;
  PD_B.ginv[7] = D18;
  PD_B.ginv[15] = D28;
  PD_B.ginv[23] = D38;
  PD_B.ginv[31] = D48;
  PD_B.ginv[39] = D45_tmp;
  PD_B.ginv[47] = D46_tmp_q;
  PD_B.ginv[55] = D46_tmp_s;
  PD_B.ginv[63] = D48_tmp_0;

  /* :  CM = CMatrix(q, dq, HexaConstants, ArmConstants); */
  /* 'CMatrix:3' ml1 = ArmConstants.Mass1; */
  /* 'CMatrix:4' ml2 = ArmConstants.Mass2; */
  /* 'CMatrix:6' L   = ArmConstants.Hexa_to_joint_L; */
  /* 'CMatrix:8' l1  = ArmConstants.l1_dim(1); */
  /* 'CMatrix:10' c1  = ArmConstants.MC1; */
  /* 'CMatrix:11' c2  = ArmConstants.MC2; */
  /* 'CMatrix:13' Hb = HexaConstants.Inertia; */
  /* 'CMatrix:14' Hbx = Hb(1, 1); */
  /* 'CMatrix:14' Hby = Hb(2, 2); */
  /* 'CMatrix:14' Hbz = Hb(3, 3); */
  /* 'CMatrix:16' H1 = ArmConstants.Inertia1; */
  /* 'CMatrix:17' H1xx = H1(1, 1); */
  /* 'CMatrix:17' H1yy = H1(2, 2); */
  /* 'CMatrix:17' H1zz = H1(3, 3); */
  /* 'CMatrix:18' H1xy = H1(1, 2); */
  /* 'CMatrix:18' H1yz = H1(2, 3); */
  /* 'CMatrix:18' H1zx = H1(1, 3); */
  /* 'CMatrix:20' H2 = ArmConstants.Inertia2; */
  /* 'CMatrix:21' H2xx = H2(1, 1); */
  /* 'CMatrix:21' H2yy = H2(2, 2); */
  /* 'CMatrix:21' H2zz = H2(3, 3); */
  /* 'CMatrix:22' H2xy = H2(1, 2); */
  /* 'CMatrix:22' H2yz = H2(2, 3); */
  /* 'CMatrix:22' H2zx = H2(1, 3); */
  /* 'CMatrix:24' phi = xi(4); */
  /* 'CMatrix:25' th  = xi(5); */
  /* 'CMatrix:26' psi = xi(6); */
  /* 'CMatrix:27' q1  = xi(7); */
  /* 'CMatrix:28' q2  = xi(8); */
  /* 'CMatrix:30' dphi = dxi(4); */
  /* 'CMatrix:31' dth  = dxi(5); */
  /* 'CMatrix:32' dpsi = dxi(6); */
  /* 'CMatrix:33' dq1  = dxi(7); */
  /* 'CMatrix:34' dq2  = dxi(8); */
  /* 'CMatrix:36' [C14, C15, C16, C17, C18] = get_C1(); */
  /* 'CMatrix:58' C14=(1/2)*(2*dth*cos(psi)*cos(th)*(L*(ml1+ml2)*sin(phi)+(c1*ml1+l1* ... */
  /* 'CMatrix:59'   ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+c2*dq2*ml2*(cos(phi- ... */
  /* 'CMatrix:60'   psi+q1+q2)-cos(phi+psi+q1+q2)+2*cos(psi)*cos(phi+q1+q2)*sin(th) ... */
  /* 'CMatrix:61'   )+2*dq1*cos(q1)*(cos(phi)*(c2*ml2*sin(psi)*sin(q2)+cos(psi)*( ... */
  /* 'CMatrix:62'   c1*ml1+l1*ml2+c2*ml2*cos(q2))*sin(th))+sin(phi)*((c1*ml1+l1*ml2+ ... */
  /* 'CMatrix:63'   c2*ml2*cos(q2))*sin(psi)-c2*ml2*cos(psi)*sin(q2)*sin(th)))+ ... */
  /* 'CMatrix:64'   (-2)*dq1*sin(q1)*(sin(phi)*(c2*ml2*sin(psi)*sin(q2)+cos(psi)*( ... */
  /* 'CMatrix:65'   c1*ml1+l1*ml2+c2*ml2*cos(q2))*sin(th))+cos(phi)*(-(c1*ml1+ ... */
  /* 'CMatrix:66'   l1*ml2+c2*ml2*cos(q2))*sin(psi)+c2*ml2*cos(psi)*sin(q2)*sin(th)) ... */
  /* 'CMatrix:67'   )+dphi*(2*cos(phi)*(sin(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2* ... */
  /* 'CMatrix:68'   sin(q1+q2))+cos(psi)*(L*(ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2* ... */
  /* 'CMatrix:69'   cos(q1+q2))*sin(th))+2*sin(phi)*((L*(ml1+ml2)+(c1*ml1+l1*ml2)* ... */
  /* 'CMatrix:70'   cos(q1)+c2*ml2*cos(q1+q2))*sin(psi)-cos(psi)*((c1*ml1+l1* ... */
  /* 'CMatrix:71'   ml2)*sin(q1)+c2*ml2*sin(q1+q2))*sin(th)))+dpsi*(2*sin(phi)*(cos( ... */
  /* 'CMatrix:72'   psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))-(L*(ml1+ ... */
  /* 'CMatrix:73'   ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin(psi)*sin(th)) ... */
  /* 'CMatrix:74'   +(-2)*cos(phi)*(cos(psi)*(L*(ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+ ... */
  /* 'CMatrix:75'   c2*ml2*cos(q1+q2))+sin(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin( ... */
  /* 'CMatrix:76'   q1+q2))*sin(th)))); */
  /* 'CMatrix:77' C15=dpsi*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2* ... */
  /* 'CMatrix:78'   cos(phi+q1+q2))*cos(th)*sin(psi)+c2*dq2*ml2*cos(psi)*cos(th)*sin( ... */
  /* 'CMatrix:79'   phi+q1+q2)+dq1*cos(psi)*cos(th)*((c1*ml1+l1*ml2)*sin(phi+q1)+c2* ... */
  /* 'CMatrix:80'   ml2*sin(phi+q1+q2))+dphi*cos(psi)*cos(th)*(L*(ml1+ml2)*sin(phi)+( ... */
  /* 'CMatrix:81'   c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+dth*cos(psi)*( ... */
  /* 'CMatrix:82'   L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+ ... */
  /* 'CMatrix:83'   q1+q2))*sin(th); */
  /* 'CMatrix:84' C16=(1/2)*(2*dth*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+ ... */
  /* 'CMatrix:85'   c2*ml2*cos(phi+q1+q2))*cos(th)*sin(psi)+(-2)*c2*dq2*ml2*(sin(q1+ ... */
  /* 'CMatrix:86'   q2)*(-cos(psi)*sin(phi)+cos(phi)*sin(psi)*sin(th))+cos(q1+q2)* ... */
  /* 'CMatrix:87'   (cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th)))+(-2)*dq1*(-(( ... */
  /* 'CMatrix:88'   c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))*(cos(psi)*sin(phi)+(-1) ... */
  /* 'CMatrix:89'   *cos(phi)*sin(psi)*sin(th))+(c1*ml1+l1*ml2)*cos(q1)*(cos(phi)* ... */
  /* 'CMatrix:90'   cos(psi)+sin(phi)*sin(psi)*sin(th))+c2*ml2*cos(q1+q2)*(cos(phi)* ... */
  /* 'CMatrix:91'   cos(psi)+sin(phi)*sin(psi)*sin(th)))+dpsi*(2*cos(phi)*(sin(psi)*(( ... */
  /* 'CMatrix:92'   c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))+cos(psi)*(L*(ml1+ml2)+( ... */
  /* 'CMatrix:93'   c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin(th))+(-2)*sin(phi) ... */
  /* 'CMatrix:94'   *(-(L*(ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))* ... */
  /* 'CMatrix:95'   sin(psi)+cos(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))* ... */
  /* 'CMatrix:96'   sin(th)))+dphi*(2*sin(phi)*(cos(psi)*((c1*ml1+l1*ml2)*sin(q1)+ ... */
  /* 'CMatrix:97'   c2*ml2*sin(q1+q2))-(L*(ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2* ... */
  /* 'CMatrix:98'   ml2*cos(q1+q2))*sin(psi)*sin(th))+(-2)*cos(phi)*(cos(psi)*(L*( ... */
  /* 'CMatrix:99'   ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))+sin(psi)*(( ... */
  /* 'CMatrix:100'   c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))*sin(th)))); */
  /* 'CMatrix:101' C17=(1/2)*(cos(psi)*(dth*(c1*ml1+l1*ml2)*cos(q1)*cos(th)*sin(phi)+ ... */
  /* 'CMatrix:102'   c2*dth*ml2*cos(q1+q2)*cos(th)*sin(phi)+2*c1*dpsi*ml1*sin(phi)* ... */
  /* 'CMatrix:103'   sin(q1)+2*dpsi*l1*ml2*sin(phi)*sin(q1)+c1*dth*ml1*cos(th)*sin( ... */
  /* 'CMatrix:104'   phi+q1)+dth*l1*ml2*cos(th)*sin(phi+q1)+2*c2*dpsi*ml2*sin(phi)* ... */
  /* 'CMatrix:105'   sin(q1+q2)+c2*dth*ml2*cos(th)*sin(phi+q1+q2)+(-2)*c1*dphi*ml1* ... */
  /* 'CMatrix:106'   sin(phi)*sin(q1)*sin(th)+(-2)*c1*dq1*ml1*sin(phi)*sin(q1)*sin( ... */
  /* 'CMatrix:107'   th)+(-2)*dphi*l1*ml2*sin(phi)*sin(q1)*sin(th)+(-2)*dq1*l1*ml2* ... */
  /* 'CMatrix:108'   sin(phi)*sin(q1)*sin(th)+(-2)*c2*dphi*ml2*sin(phi)*sin(q1+q2)* ... */
  /* 'CMatrix:109'   sin(th)+(-2)*c2*dq1*ml2*sin(phi)*sin(q1+q2)*sin(th)+(-2)*c2* ... */
  /* 'CMatrix:110'   dq2*ml2*sin(phi)*sin(q1+q2)*sin(th))+2*sin(phi)*sin(psi)*((c1* ... */
  /* 'CMatrix:111'   ml1+l1*ml2)*cos(q1)*(dphi+dq1-dpsi*sin(th))+c2*ml2*cos(q1+ ... */
  /* 'CMatrix:112'   q2)*(dphi+dq1+dq2-dpsi*sin(th)))+cos(phi)*(cos(psi)*(c1*dth* ... */
  /* 'CMatrix:113'   ml1*cos(th)*sin(q1)+dth*l1*ml2*cos(th)*sin(q1)+c2*dth*ml2*cos( ... */
  /* 'CMatrix:114'   th)*sin(q1+q2)-c2*dphi*ml2*sin(q1)*sin(q2)*sin(th)- ... */
  /* 'CMatrix:115'   c2*ml2*cos(q1+q2)*(2*dpsi-(dphi+2*(dq1+dq2))*sin(th))+cos( ... */
  /* 'CMatrix:116'   q1)*((-2)*dpsi*(c1*ml1+l1*ml2)+(2*(dphi+dq1)*(c1*ml1+l1*ml2)+ ... */
  /* 'CMatrix:117'   c2*dphi*ml2*cos(q2))*sin(th)))+sin(psi)*(c2*ml2*(dphi*cos(q1)* ... */
  /* 'CMatrix:118'   sin(q2)+sin(q1+q2)*(dphi+2*(dq1+dq2)+(-2)*dpsi*sin(th)))+sin(q1)*( ... */
  /* 'CMatrix:119'   c2*dphi*ml2*cos(q2)+2*(c1*ml1+l1*ml2)*(dphi+dq1-dpsi*sin( ... */
  /* 'CMatrix:120'   th)))))); */
  /* 'CMatrix:121' C18=(1/2)*c2*ml2*(2*cos(q1+q2)*sin(phi)*sin(psi)*(dphi+dq1+dq2- ... */
  /* 'CMatrix:122'   dpsi*sin(th))+cos(psi)*(dth*cos(q1+q2)*cos(th)*sin(phi)+dth*cos( ... */
  /* 'CMatrix:123'   th)*sin(phi+q1+q2)+2*sin(phi)*sin(q1+q2)*(dpsi-(dphi+dq1+dq2) ... */
  /* 'CMatrix:124'   *sin(th)))+cos(phi)*(2*sin(psi)*sin(q1+q2)*(dphi+dq1+dq2- ... */
  /* 'CMatrix:125'   dpsi*sin(th))+cos(psi)*(dth*cos(th)*sin(q1+q2)+2*cos(q1+q2)*((-1) ... */
  /* 'CMatrix:126'   *dpsi+(dphi+dq1+dq2)*sin(th))))); */
  /* 'CMatrix:37' [C24, C25, C26, C27, C28] = get_C2(); */
  /* 'CMatrix:130' C24=-dq1*cos(psi)*((c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+ ... */
  /* 'CMatrix:131'   q1+q2))+dth*cos(th)*sin(psi)*(L*(ml1+ml2)*sin(phi)+(c1*ml1+l1* ... */
  /* 'CMatrix:132'   ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+(-1/4)*c2*dq2*ml2*(cos( ... */
  /* 'CMatrix:133'   phi-psi+q1+q2-th)-cos(phi+psi+q1+q2-th)- ... */
  /* 'CMatrix:134'   cos(phi-psi+q1+q2+th)+cos(phi+psi+q1+q2+th)+2*sin(phi-psi+ ... */
  /* 'CMatrix:135'   q1+q2)+2*sin(phi+psi+q1+q2))+dq1*((c1*ml1+l1*ml2)*cos(phi+q1)+c2* ... */
  /* 'CMatrix:136'   ml2*cos(phi+q1+q2))*sin(psi)*sin(th)+dphi*(-cos(psi)*(L*(ml1+ ... */
  /* 'CMatrix:137'   ml2)*sin(phi)+(c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+( ... */
  /* 'CMatrix:138'   L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+ ... */
  /* 'CMatrix:139'   q1+q2))*sin(psi)*sin(th))+dpsi*(sin(phi)*(sin(psi)*((c1*ml1+l1* ... */
  /* 'CMatrix:140'   ml2)*sin(q1)+c2*ml2*sin(q1+q2))+cos(psi)*(L*(ml1+ml2)+(c1*ml1+l1* ... */
  /* 'CMatrix:141'   ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin(th))+cos(phi)*(-(L*(ml1+ ... */
  /* 'CMatrix:142'   ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin(psi)+cos(psi) ... */
  /* 'CMatrix:143'   *((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))*sin(th))); */
  /* 'CMatrix:144' C25=-dpsi*cos(psi)*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos( ... */
  /* 'CMatrix:145'   phi+q1)+c2*ml2*cos(phi+q1+q2))*cos(th)+c2*dq2*ml2*cos(th)*sin( ... */
  /* 'CMatrix:146'   psi)*sin(phi+q1+q2)+dq1*cos(th)*sin(psi)*((c1*ml1+l1*ml2)*sin( ... */
  /* 'CMatrix:147'   phi+q1)+c2*ml2*sin(phi+q1+q2))+dphi*cos(th)*sin(psi)*(L*(ml1+ml2) ... */
  /* 'CMatrix:148'   *sin(phi)+(c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+dth* ... */
  /* 'CMatrix:149'   (L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+ ... */
  /* 'CMatrix:150'   q1+q2))*sin(psi)*sin(th); */
  /* 'CMatrix:151' C26=(1/2)*((-2)*cos(psi)*(dth*(c1*ml1+l1*ml2)*cos(phi+q1)*cos(th)+ ... */
  /* 'CMatrix:152'   c2*dth*ml2*cos(phi+q1+q2)*cos(th)+sin(phi)*(L*(ml1+ml2)*(dpsi+( ... */
  /* 'CMatrix:153'   -1)*dphi*sin(th))+(c1*ml1+l1*ml2)*cos(q1)*(dpsi-(dphi+dq1)* ... */
  /* 'CMatrix:154'   sin(th))+c2*ml2*cos(q1+q2)*(dpsi-(dphi+dq1+dq2)*sin(th))))+( ... */
  /* 'CMatrix:155'   -1)*cos(phi)*(2*cos(psi)*(dth*L*(ml1+ml2)*cos(th)+(c1*ml1+l1* ... */
  /* 'CMatrix:156'   ml2)*sin(q1)*(dpsi-(dphi+dq1)*sin(th))+c2*ml2*sin(q1+q2)*( ... */
  /* 'CMatrix:157'   dpsi-(dphi+dq1+dq2)*sin(th)))+sin(psi)*(2*L*(ml1+ml2)*(dphi+( ... */
  /* 'CMatrix:158'   -1)*dpsi*sin(th))+(-1/2)*c2*ml2*cos(q1+q2)*((-3)*dphi+(-4)*dq1+( ... */
  /* 'CMatrix:159'   -4)*dq2+dphi*cos(2*th)+4*dpsi*sin(th))+cos(q1)*(2*c1*(dphi+dq1) ... */
  /* 'CMatrix:160'   *ml1+(dphi+2*dq1)*l1*ml2+(-2)*dpsi*(c1*ml1+l1*ml2)*sin(th)+ ... */
  /* 'CMatrix:161'   dphi*l1*ml2*sin(th)^2)))+sin(psi)*(-dphi*l1*ml2*cos(phi+q1) ... */
  /* 'CMatrix:162'   *cos(th)^2-c2*dphi*ml2*cos(phi+q1+q2)*cos(th)^2+sin(phi)*( ... */
  /* 'CMatrix:163'   c2*ml2*sin(q1+q2)*(dphi+2*(dq1+dq2)+(-2)*dpsi*sin(th)+dphi*sin( ... */
  /* 'CMatrix:164'   th)^2)+sin(q1)*(2*c1*(dphi+dq1)*ml1+(dphi+2*dq1)*l1*ml2+(-2)* ... */
  /* 'CMatrix:165'   dpsi*(c1*ml1+l1*ml2)*sin(th)+dphi*l1*ml2*sin(th)^2)))); */
  D14 = std::sin(rtu_InBus1_Positions[4]);
  D15 = std::cos(rtu_InBus1_Positions[4]);
  D16 = std::cos(rtu_InBus1_Positions[4]);
  D17 = std::sin(rtu_InBus1_Positions[4]);
  D18 = std::sin(rtu_InBus1_Positions[4]);

  /* 'CMatrix:166' C27=-dphi*cos(psi)*((c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+ ... */
  /* 'CMatrix:167'   q1+q2))+dth*cos(th)*sin(psi)*((c1*ml1+l1*ml2)*sin(phi+q1)+c2* ... */
  /* 'CMatrix:168'   ml2*sin(phi+q1+q2))+dphi*((c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos( ... */
  /* 'CMatrix:169'   phi+q1+q2))*sin(psi)*sin(th)-c2*dq2*ml2*(cos(psi)*sin(phi+ ... */
  /* 'CMatrix:170'   q1+q2)-cos(phi+q1+q2)*sin(psi)*sin(th))+dq1*(-cos(psi)*(( ... */
  /* 'CMatrix:171'   c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+((c1*ml1+l1* ... */
  /* 'CMatrix:172'   ml2)*cos(phi+q1)+c2*ml2*cos(phi+q1+q2))*sin(psi)*sin(th))+dpsi*( ... */
  /* 'CMatrix:173'   sin(phi)*(sin(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))+ ... */
  /* 'CMatrix:174'   cos(psi)*((c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin(th))+ ... */
  /* 'CMatrix:175'   cos(phi)*(-((c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin( ... */
  /* 'CMatrix:176'   psi)+cos(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))*sin(th) ... */
  /* 'CMatrix:177'   )); */
  /* 'CMatrix:178' C28=(-1/2)*c2*ml2*(2*cos(psi)*sin(phi+q1+q2)*(dphi+dq1+dq2- ... */
  /* 'CMatrix:179'   dpsi*sin(th))+sin(psi)*(2*dpsi*cos(phi+q1+q2)+(dphi+dq1+dq2- ... */
  /* 'CMatrix:180'   dth)*sin(phi+q1+q2-th)-(dphi+dq1+dq2+dth)*sin(phi+q1+q2+ ... */
  /* 'CMatrix:181'   th))); */
  /* 'CMatrix:38' [C34, C35, C36, C37, C38] = get_C3(); */
  /* 'CMatrix:185' C34=c2*dq2*ml2*cos(phi+q1+q2)*cos(th)+dq1*((c1*ml1+l1*ml2)*cos(phi+ ... */
  /* 'CMatrix:186'   q1)+c2*ml2*cos(phi+q1+q2))*cos(th)+dphi*(L*(ml1+ml2)*cos(phi)+( ... */
  /* 'CMatrix:187'   c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+q1+q2))*cos(th)- ... */
  /* 'CMatrix:188'   dth*(L*(ml1+ml2)*sin(phi)+(c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2* ... */
  /* 'CMatrix:189'   sin(phi+q1+q2))*sin(th); */
  /* 'CMatrix:190' C35=dth*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2* ... */
  /* 'CMatrix:191'   cos(phi+q1+q2))*cos(th)-c2*dq2*ml2*sin(phi+q1+q2)*sin(th)+( ... */
  /* 'CMatrix:192'   -1)*dq1*((c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))*sin( ... */
  /* 'CMatrix:193'   th)-dphi*(L*(ml1+ml2)*sin(phi)+(c1*ml1+l1*ml2)*sin(phi+q1)+ ... */
  /* 'CMatrix:194'   c2*ml2*sin(phi+q1+q2))*sin(th); */
  /* 'CMatrix:195' C36=0; */
  /* 'CMatrix:196' C37=(dphi+dq1)*(c1*ml1+l1*ml2)*cos(phi+q1)*cos(th)+c2*(dphi+dq1+dq2)* ... */
  /* 'CMatrix:197'   ml2*cos(phi+q1+q2)*cos(th)-dth*((c1*ml1+l1*ml2)*sin(phi+q1)+ ... */
  /* 'CMatrix:198'   c2*ml2*sin(phi+q1+q2))*sin(th); */
  /* 'CMatrix:199' C38=c2*ml2*((dphi+dq1+dq2)*cos(phi+q1+q2)*cos(th)-dth*sin(phi+q1+ ... */
  /* 'CMatrix:200'   q2)*sin(th)); */
  /* 'CMatrix:39' [C44, C45, C46, C47, C48] = get_C4(); */
  /* 'CMatrix:204' C44=-dq1*L*(c1*ml1+l1*ml2)*sin(q1)-c2*ml2*(dq2*l1*sin( ... */
  /* 'CMatrix:205'   q2)+(dq1+dq2)*L*sin(q1+q2)); */
  /* 'CMatrix:206' C45=(1/4)*(2*dth*((-2)*H1xy*cos(2*(phi+q1))+(-2)*H2xy*cos(2*(phi+ ... */
  /* 'CMatrix:207'   q1+q2))+Hby*sin(2*phi)-Hbz*sin(2*phi)+L^2*ml1*sin(2*phi)+ ... */
  /* 'CMatrix:208'   L^2*ml2*sin(2*phi)-H1xx*sin(2*(phi+q1))+H1yy*sin(2*(phi+ ... */
  /* 'CMatrix:209'   q1))+c1^2*ml1*sin(2*(phi+q1))+l1^2*ml2*sin(2*(phi+q1))+2*c1* ... */
  /* 'CMatrix:210'   L*ml1*sin(2*phi+q1)+2*L*l1*ml2*sin(2*phi+q1)-H2xx*sin(2* ... */
  /* 'CMatrix:211'   (phi+q1+q2))+H2yy*sin(2*(phi+q1+q2))+c2^2*ml2*sin(2*(phi+q1+q2))+ ... */
  /* 'CMatrix:212'   2*c2*L*ml2*sin(2*phi+q1+q2)+2*c2*l1*ml2*sin(2*(phi+q1)+q2))+( ... */
  /* 'CMatrix:213'   -1)*dpsi*((Hby-Hbz+L^2*(ml1+ml2))*cos(2*phi-th)+2*L* ... */
  /* 'CMatrix:214'   (c1*ml1+l1*ml2)*cos(q1-th)+2*H1yz*cos(phi+q1-th)+2* ... */
  /* 'CMatrix:215'   c1*L*ml1*cos(2*phi+q1-th)+2*L*l1*ml2*cos(2*phi+q1- ... */
  /* 'CMatrix:216'   th)-H1xx*cos(2*phi+2*q1-th)+H1yy*cos(2*phi+2*q1- ... */
  /* 'CMatrix:217'   th)+c1^2*ml1*cos(2*phi+2*q1-th)+l1^2*ml2*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:218'   -th)+2*c2*l1*ml2*cos(q2-th)+2*c2*L*ml2*cos(q1+q2+(-1) ... */
  /* 'CMatrix:219'   *th)+2*H2yz*cos(phi+q1+q2-th)+2*c2*L*ml2*cos(2*phi+q1+q2+( ... */
  /* 'CMatrix:220'   -1)*th)+2*c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx*cos( ... */
  /* 'CMatrix:221'   2*phi+2*q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:222'   c2^2*ml2*cos(2*phi+2*q1+2*q2-th)+2*H1zz*cos(th)+2*H2zz* ... */
  /* 'CMatrix:223'   cos(th)+2*Hbx*cos(th)+2*c1^2*ml1*cos(th)+2*L^2*ml1*cos(th)+2* ... */
  /* 'CMatrix:224'   c2^2*ml2*cos(th)+2*L^2*ml2*cos(th)+2*l1^2*ml2*cos(th)+Hby* ... */
  /* 'CMatrix:225'   cos(2*phi+th)-Hbz*cos(2*phi+th)+L^2*ml1*cos(2*phi+th)+ ... */
  /* 'CMatrix:226'   L^2*ml2*cos(2*phi+th)+2*c1*L*ml1*cos(q1+th)+2*L*l1*ml2*cos( ... */
  /* 'CMatrix:227'   q1+th)+(-2)*H1yz*cos(phi+q1+th)+2*c1*L*ml1*cos(2*phi+q1+th)+2* ... */
  /* 'CMatrix:228'   L*l1*ml2*cos(2*phi+q1+th)-H1xx*cos(2*phi+2*q1+th)+H1yy* ... */
  /* 'CMatrix:229'   cos(2*phi+2*q1+th)+c1^2*ml1*cos(2*phi+2*q1+th)+l1^2*ml2*cos( ... */
  /* 'CMatrix:230'   2*phi+2*q1+th)+2*c2*l1*ml2*cos(q2+th)+2*c2*L*ml2*cos(q1+q2+th) ... */
  /* 'CMatrix:231'   +(-2)*H2yz*cos(phi+q1+q2+th)+2*c2*L*ml2*cos(2*phi+q1+q2+th)+2* ... */
  /* 'CMatrix:232'   c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx*cos(2*phi+2*q1+2*q2+ ... */
  /* 'CMatrix:233'   th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2*cos(2*phi+2*q1+2*q2+ ... */
  /* 'CMatrix:234'   th)+2*H1zx*sin(phi+q1-th)+2*H1xy*sin(2*phi+2*q1-th)+ ... */
  /* 'CMatrix:235'   2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:236'   th)+(-2)*H1zx*sin(phi+q1+th)+2*H1xy*sin(2*phi+2*q1+th)+(-2)* ... */
  /* 'CMatrix:237'   H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+2*q2+th))); */
  /* 'CMatrix:238' C46=(1/8)*(4*dpsi*H1xy*cos(2*(phi+q1))+4*dpsi*H2xy*cos(2*(phi+q1+ ... */
  /* 'CMatrix:239'   q2))+2*dpsi*H1zx*cos(phi+q1+(-2)*th)+2*dpsi*H2zx*cos(phi+q1+q2+( ... */
  /* 'CMatrix:240'   -2)*th)+(-2)*dth*Hby*cos(2*phi-th)+2*dth*Hbz*cos(2*phi+( ... */
  /* 'CMatrix:241'   -1)*th)+(-2)*dth*L^2*ml1*cos(2*phi-th)+(-2)*dth*L^2* ... */
  /* 'CMatrix:242'   ml2*cos(2*phi-th)+(-4)*c1*dth*L*ml1*cos(q1-th)+(-4)* ... */
  /* 'CMatrix:243'   dth*L*l1*ml2*cos(q1-th)+(-4)*dth*H1yz*cos(phi+q1-th)+ ... */
  /* 'CMatrix:244'   2*dpsi*H1xy*cos(2*(phi+q1-th))+(-4)*c1*dth*L*ml1*cos(2* ... */
  /* 'CMatrix:245'   phi+q1-th)+(-4)*dth*L*l1*ml2*cos(2*phi+q1-th)+2*dth* ... */
  /* 'CMatrix:246'   H1xx*cos(2*phi+2*q1-th)+(-2)*dth*H1yy*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:247'   *th)+(-2)*c1^2*dth*ml1*cos(2*phi+2*q1-th)+(-2)*dth* ... */
  /* 'CMatrix:248'   l1^2*ml2*cos(2*phi+2*q1-th)+(-4)*c2*dth*l1*ml2*cos(q2+( ... */
  /* 'CMatrix:249'   -1)*th)+(-4)*c2*dth*L*ml2*cos(q1+q2-th)+(-4)*dth*H2yz* ... */
  /* 'CMatrix:250'   cos(phi+q1+q2-th)+2*dpsi*H2xy*cos(2*(phi+q1+q2-th))+(-4) ... */
  /* 'CMatrix:251'   *c2*dth*L*ml2*cos(2*phi+q1+q2-th)+(-4)*c2*dth*l1*ml2* ... */
  /* 'CMatrix:252'   cos(2*phi+2*q1+q2-th)+2*dth*H2xx*cos(2*phi+2*q1+2*q2+(-1) ... */
  /* 'CMatrix:253'   *th)+(-2)*dth*H2yy*cos(2*phi+2*q1+2*q2-th)+(-2)*c2^2* ... */
  /* 'CMatrix:254'   dth*ml2*cos(2*phi+2*q1+2*q2-th)+(-4)*dth*H1zz*cos(th)+(-4) ... */
  /* 'CMatrix:255'   *dth*H2zz*cos(th)+(-4)*dth*Hbx*cos(th)+(-4)*c1^2*dth*ml1*cos( ... */
  /* 'CMatrix:256'   th)+(-4)*dth*L^2*ml1*cos(th)+(-4)*c2^2*dth*ml2*cos(th)+(-4)* ... */
  /* 'CMatrix:257'   dth*L^2*ml2*cos(th)+(-4)*dth*l1^2*ml2*cos(th)+(-2)*dth*Hby* ... */
  /* 'CMatrix:258'   cos(2*phi+th)+2*dth*Hbz*cos(2*phi+th)+(-2)*dth*L^2*ml1*cos(2* ... */
  /* 'CMatrix:259'   phi+th)+(-2)*dth*L^2*ml2*cos(2*phi+th)+(-4)*c1*dth*L*ml1*cos( ... */
  /* 'CMatrix:260'   q1+th)+(-4)*dth*L*l1*ml2*cos(q1+th)+4*dth*H1yz*cos(phi+q1+th)+ ... */
  /* 'CMatrix:261'   2*dpsi*H1xy*cos(2*(phi+q1+th))+(-4)*c1*dth*L*ml1*cos(2*phi+q1+ ... */
  /* 'CMatrix:262'   th)+(-4)*dth*L*l1*ml2*cos(2*phi+q1+th)+2*dth*H1xx*cos(2*phi+ ... */
  /* 'CMatrix:263'   2*q1+th)+(-2)*dth*H1yy*cos(2*phi+2*q1+th)+(-2)*c1^2*dth*ml1* ... */
  /* 'CMatrix:264'   cos(2*phi+2*q1+th)+(-2)*dth*l1^2*ml2*cos(2*phi+2*q1+th)+(-4)* ... */
  /* 'CMatrix:265'   c2*dth*l1*ml2*cos(q2+th)+(-4)*c2*dth*L*ml2*cos(q1+q2+th)+4* ... */
  /* 'CMatrix:266'   dth*H2yz*cos(phi+q1+q2+th)+2*dpsi*H2xy*cos(2*(phi+q1+q2+th))+(-4) ... */
  /* 'CMatrix:267'   *c2*dth*L*ml2*cos(2*phi+q1+q2+th)+(-4)*c2*dth*l1*ml2*cos(2* ... */
  /* 'CMatrix:268'   phi+2*q1+q2+th)+2*dth*H2xx*cos(2*phi+2*q1+2*q2+th)+(-2)*dth* ... */
  /* 'CMatrix:269'   H2yy*cos(2*phi+2*q1+2*q2+th)+(-2)*c2^2*dth*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:270'   q1+2*q2+th)+(-2)*dpsi*H1zx*cos(phi+q1+2*th)+(-2)*dpsi*H2zx*cos( ... */
  /* 'CMatrix:271'   phi+q1+q2+2*th)+(-2)*dpsi*Hby*sin(2*phi)+2*dpsi*Hbz*sin(2*phi)+ ... */
  /* 'CMatrix:272'   (-2)*dpsi*L^2*ml1*sin(2*phi)+(-2)*dpsi*L^2*ml2*sin(2*phi)+ ... */
  /* 'CMatrix:273'   2*dpsi*H1xx*sin(2*(phi+q1))+(-2)*dpsi*H1yy*sin(2*(phi+q1))+(-2) ... */
  /* 'CMatrix:274'   *c1^2*dpsi*ml1*sin(2*(phi+q1))+(-2)*dpsi*l1^2*ml2*sin(2*( ... */
  /* 'CMatrix:275'   phi+q1))+(-4)*c1*dpsi*L*ml1*sin(2*phi+q1)+(-4)*dpsi*L*l1*ml2* ... */
  /* 'CMatrix:276'   sin(2*phi+q1)+2*dpsi*H2xx*sin(2*(phi+q1+q2))+(-2)*dpsi*H2yy*sin( ... */
  /* 'CMatrix:277'   2*(phi+q1+q2))+(-2)*c2^2*dpsi*ml2*sin(2*(phi+q1+q2))+(-4)*c2* ... */
  /* 'CMatrix:278'   dpsi*L*ml2*sin(2*phi+q1+q2)+(-4)*c2*dpsi*l1*ml2*sin(2*(phi+q1) ... */
  /* 'CMatrix:279'   +q2)+(-2)*c2*dpsi*l1*ml2*sin(q2+2*(phi+q1-th))+(-2)*dpsi* ... */
  /* 'CMatrix:280'   H1yz*sin(phi+q1+(-2)*th)+(-2)*c1*dpsi*L*ml1*sin(2*phi+q1+(-2)* ... */
  /* 'CMatrix:281'   th)+(-2)*dpsi*L*l1*ml2*sin(2*phi+q1+(-2)*th)+(-2)*dpsi*H2yz* ... */
  /* 'CMatrix:282'   sin(phi+q1+q2+(-2)*th)+(-2)*c2*dpsi*L*ml2*sin(2*phi+q1+q2+(-2)* ... */
  /* 'CMatrix:283'   th)+dpsi*Hbz*sin(2*(phi-th))+(-4)*dth*H1zx*sin(phi+q1- ... */
  /* 'CMatrix:284'   th)+dpsi*H1xx*sin(2*(phi+q1-th))-dpsi*H1yy*sin(2*(phi+ ... */
  /* 'CMatrix:285'   q1-th))-c1^2*dpsi*ml1*sin(2*(phi+q1-th))- ... */
  /* 'CMatrix:286'   dpsi*l1^2*ml2*sin(2*(phi+q1-th))+(-4)*dth*H1xy*sin(2*phi+ ... */
  /* 'CMatrix:287'   2*q1-th)+(-4)*dth*H2zx*sin(phi+q1+q2-th)+dpsi*H2xx* ... */
  /* 'CMatrix:288'   sin(2*(phi+q1+q2-th))-dpsi*H2yy*sin(2*(phi+q1+q2- ... */
  /* 'CMatrix:289'   th))-c2^2*dpsi*ml2*sin(2*(phi+q1+q2-th))+(-4)*dth* ... */
  /* 'CMatrix:290'   H2xy*sin(2*phi+2*q1+2*q2-th)+8*c2*dq2*ml2*(l1*sin(q2)+L* ... */
  /* 'CMatrix:291'   sin(q1+q2))*sin(th)+8*dq1*L*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2* ... */
  /* 'CMatrix:292'   sin(q1+q2))*sin(th)+dpsi*Hby*sin(2*(-phi+th))+dpsi*L^2*ml1* ... */
  /* 'CMatrix:293'   sin(2*(-phi+th))+dpsi*L^2*ml2*sin(2*(-phi+th))- ... */
  /* 'CMatrix:294'   dpsi*Hby*sin(2*(phi+th))+dpsi*Hbz*sin(2*(phi+th))-dpsi* ... */
  /* 'CMatrix:295'   L^2*ml1*sin(2*(phi+th))-dpsi*L^2*ml2*sin(2*(phi+th))+4* ... */
  /* 'CMatrix:296'   dth*H1zx*sin(phi+q1+th)+dpsi*H1xx*sin(2*(phi+q1+th))-dpsi* ... */
  /* 'CMatrix:297'   H1yy*sin(2*(phi+q1+th))-c1^2*dpsi*ml1*sin(2*(phi+q1+th))+( ... */
  /* 'CMatrix:298'   -1)*dpsi*l1^2*ml2*sin(2*(phi+q1+th))+(-4)*dth*H1xy*sin(2*phi+ ... */
  /* 'CMatrix:299'   2*q1+th)+4*dth*H2zx*sin(phi+q1+q2+th)+dpsi*H2xx*sin(2*(phi+q1+q2+ ... */
  /* 'CMatrix:300'   th))-dpsi*H2yy*sin(2*(phi+q1+q2+th))-c2^2*dpsi*ml2* ... */
  /* 'CMatrix:301'   sin(2*(phi+q1+q2+th))+(-4)*dth*H2xy*sin(2*phi+2*q1+2*q2+th)+2* ... */
  /* 'CMatrix:302'   dpsi*H1yz*sin(phi+q1+2*th)+2*dpsi*H2yz*sin(phi+q1+q2+2*th)+(-2)* ... */
  /* 'CMatrix:303'   c1*dpsi*L*ml1*sin(q1+2*(phi+th))+(-2)*dpsi*L*l1*ml2*sin(q1+2* ... */
  /* 'CMatrix:304'   (phi+th))+(-2)*c2*dpsi*L*ml2*sin(q1+q2+2*(phi+th))+(-2)*c2* ... */
  /* 'CMatrix:305'   dpsi*l1*ml2*sin(q2+2*(phi+q1+th))); */
  /* 'CMatrix:306' C47=-c2*dq2*ml2*(l1*sin(q2)+L*sin(q1+q2))-L*((c1*ml1+l1* ... */
  /* 'CMatrix:307'   ml2)*sin(q1)+c2*ml2*sin(q1+q2))*(dphi+dq1-dpsi*sin(th)); */
  /* 'CMatrix:308' C48=-c2*ml2*(l1*sin(q2)+L*sin(q1+q2))*(dphi+dq1+dq2-dpsi* ... */
  /* 'CMatrix:309'   sin(th)); */
  /* 'CMatrix:40' [C54, C55, C56, C57, C58] = get_C5(); */
  /* 'CMatrix:314' C54=(1/4)*(4*(dphi+dq1)*H1zx*cos(phi+q1)+4*dth*H1xy*cos(2*(phi+q1))+ ... */
  /* 'CMatrix:315'   4*dphi*H2zx*cos(phi+q1+q2)+4*dq1*H2zx*cos(phi+q1+q2)+4*dq2* ... */
  /* 'CMatrix:316'   H2zx*cos(phi+q1+q2)+4*dth*H2xy*cos(2*(phi+q1+q2))+dpsi*Hby*cos( ... */
  /* 'CMatrix:317'   2*phi-th)-dpsi*Hbz*cos(2*phi-th)+dpsi*L^2*ml1* ... */
  /* 'CMatrix:318'   cos(2*phi-th)+dpsi*L^2*ml2*cos(2*phi-th)+2*c1*dpsi* ... */
  /* 'CMatrix:319'   L*ml1*cos(q1-th)+2*dpsi*L*l1*ml2*cos(q1-th)+2*dpsi* ... */
  /* 'CMatrix:320'   H1yz*cos(phi+q1-th)+2*c1*dpsi*L*ml1*cos(2*phi+q1-th)+ ... */
  /* 'CMatrix:321'   2*dpsi*L*l1*ml2*cos(2*phi+q1-th)-dpsi*H1xx*cos(2* ... */
  /* 'CMatrix:322'   phi+2*q1-th)+dpsi*H1yy*cos(2*phi+2*q1-th)+c1^2*dpsi* ... */
  /* 'CMatrix:323'   ml1*cos(2*phi+2*q1-th)+dpsi*l1^2*ml2*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:324'   *th)+2*c2*dpsi*l1*ml2*cos(q2-th)+2*c2*dpsi*L*ml2*cos( ... */
  /* 'CMatrix:325'   q1+q2-th)+2*dpsi*H2yz*cos(phi+q1+q2-th)+2*c2*dpsi*L* ... */
  /* 'CMatrix:326'   ml2*cos(2*phi+q1+q2-th)+2*c2*dpsi*l1*ml2*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:327'   q2-th)-dpsi*H2xx*cos(2*phi+2*q1+2*q2-th)+dpsi* ... */
  /* 'CMatrix:328'   H2yy*cos(2*phi+2*q1+2*q2-th)+c2^2*dpsi*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:329'   q1+2*q2-th)+2*dpsi*H1zz*cos(th)+2*dpsi*H2zz*cos(th)+2* ... */
  /* 'CMatrix:330'   dpsi*Hbx*cos(th)+2*c1^2*dpsi*ml1*cos(th)+2*dpsi*L^2*ml1*cos( ... */
  /* 'CMatrix:331'   th)+2*c2^2*dpsi*ml2*cos(th)+2*dpsi*L^2*ml2*cos(th)+2*dpsi* ... */
  /* 'CMatrix:332'   l1^2*ml2*cos(th)+dpsi*Hby*cos(2*phi+th)-dpsi*Hbz*cos(2* ... */
  /* 'CMatrix:333'   phi+th)+dpsi*L^2*ml1*cos(2*phi+th)+dpsi*L^2*ml2*cos(2*phi+th)+ ... */
  /* 'CMatrix:334'   2*c1*dpsi*L*ml1*cos(q1+th)+2*dpsi*L*l1*ml2*cos(q1+th)+(-2)* ... */
  /* 'CMatrix:335'   dpsi*H1yz*cos(phi+q1+th)+2*c1*dpsi*L*ml1*cos(2*phi+q1+th)+2* ... */
  /* 'CMatrix:336'   dpsi*L*l1*ml2*cos(2*phi+q1+th)-dpsi*H1xx*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:337'   th)+dpsi*H1yy*cos(2*phi+2*q1+th)+c1^2*dpsi*ml1*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:338'   th)+dpsi*l1^2*ml2*cos(2*phi+2*q1+th)+2*c2*dpsi*l1*ml2*cos(q2+ ... */
  /* 'CMatrix:339'   th)+2*c2*dpsi*L*ml2*cos(q1+q2+th)+(-2)*dpsi*H2yz*cos(phi+q1+q2+ ... */
  /* 'CMatrix:340'   th)+2*c2*dpsi*L*ml2*cos(2*phi+q1+q2+th)+2*c2*dpsi*l1*ml2*cos( ... */
  /* 'CMatrix:341'   2*phi+2*q1+q2+th)-dpsi*H2xx*cos(2*phi+2*q1+2*q2+th)+dpsi* ... */
  /* 'CMatrix:342'   H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*dpsi*ml2*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:343'   q2+th)+(-2)*dth*Hby*sin(2*phi)+2*dth*Hbz*sin(2*phi)+(-2)*dth* ... */
  /* 'CMatrix:344'   L^2*ml1*sin(2*phi)+(-2)*dth*L^2*ml2*sin(2*phi)+(-4)*dphi* ... */
  /* 'CMatrix:345'   H1yz*sin(phi+q1)+(-4)*dq1*H1yz*sin(phi+q1)+2*dth*H1xx*sin(2*( ... */
  /* 'CMatrix:346'   phi+q1))+(-2)*dth*H1yy*sin(2*(phi+q1))+(-2)*c1^2*dth*ml1*sin( ... */
  /* 'CMatrix:347'   2*(phi+q1))+(-2)*dth*l1^2*ml2*sin(2*(phi+q1))+(-4)*c1*dth*L* ... */
  /* 'CMatrix:348'   ml1*sin(2*phi+q1)+(-4)*dth*L*l1*ml2*sin(2*phi+q1)+(-4)*dphi* ... */
  /* 'CMatrix:349'   H2yz*sin(phi+q1+q2)+(-4)*dq1*H2yz*sin(phi+q1+q2)+(-4)*dq2*H2yz* ... */
  /* 'CMatrix:350'   sin(phi+q1+q2)+2*dth*H2xx*sin(2*(phi+q1+q2))+(-2)*dth*H2yy*sin( ... */
  /* 'CMatrix:351'   2*(phi+q1+q2))+(-2)*c2^2*dth*ml2*sin(2*(phi+q1+q2))+(-4)*c2* ... */
  /* 'CMatrix:352'   dth*L*ml2*sin(2*phi+q1+q2)+(-4)*c2*dth*l1*ml2*sin(2*(phi+q1)+ ... */
  /* 'CMatrix:353'   q2)+2*dpsi*H1zx*sin(phi+q1-th)+2*dpsi*H1xy*sin(2*phi+2*q1+ ... */
  /* 'CMatrix:354'   -th)+2*dpsi*H2zx*sin(phi+q1+q2-th)+2*dpsi*H2xy*sin(2* ... */
  /* 'CMatrix:355'   phi+2*q1+2*q2-th)+(-2)*dpsi*H1zx*sin(phi+q1+th)+2*dpsi* ... */
  /* 'CMatrix:356'   H1xy*sin(2*phi+2*q1+th)+(-2)*dpsi*H2zx*sin(phi+q1+q2+th)+2*dpsi* ... */
  /* 'CMatrix:357'   H2xy*sin(2*phi+2*q1+2*q2+th)); */
  /* 'CMatrix:358' C55=(1/2)*(2*dq2*H2xy*cos(2*(phi+q1+q2))+(-2)*dq2*(c2*L*ml2*cos( ... */
  /* 'CMatrix:359'   phi)+c2*l1*ml2*cos(phi+q1)+(-H2xx+H2yy+c2^2*ml2)*cos(phi+q1+ ... */
  /* 'CMatrix:360'   q2))*sin(phi+q1+q2)+dphi*(2*H1xy*cos(2*(phi+q1))+2*H2xy*cos(2*( ... */
  /* 'CMatrix:361'   phi+q1+q2))-Hby*sin(2*phi)+Hbz*sin(2*phi)-L^2*ml1* ... */
  /* 'CMatrix:362'   sin(2*phi)-L^2*ml2*sin(2*phi)+H1xx*sin(2*(phi+q1))- ... */
  /* 'CMatrix:363'   H1yy*sin(2*(phi+q1))-c1^2*ml1*sin(2*(phi+q1))-l1^2* ... */
  /* 'CMatrix:364'   ml2*sin(2*(phi+q1))+(-2)*c1*L*ml1*sin(2*phi+q1)+(-2)*L*l1* ... */
  /* 'CMatrix:365'   ml2*sin(2*phi+q1)+H2xx*sin(2*(phi+q1+q2))-H2yy*sin(2*(phi+ ... */
  /* 'CMatrix:366'   q1+q2))-c2^2*ml2*sin(2*(phi+q1+q2))+(-2)*c2*L*ml2*sin(2* ... */
  /* 'CMatrix:367'   phi+q1+q2)+(-2)*c2*l1*ml2*sin(2*(phi+q1)+q2))+dq1*(2*H1xy*cos( ... */
  /* 'CMatrix:368'   2*(phi+q1))+2*H2xy*cos(2*(phi+q1+q2))-c1*L*ml1*sin(q1)+(-1) ... */
  /* 'CMatrix:369'   *L*l1*ml2*sin(q1)+H1xx*sin(2*(phi+q1))-H1yy*sin(2*(phi+q1) ... */
  /* 'CMatrix:370'   )-c1^2*ml1*sin(2*(phi+q1))-l1^2*ml2*sin(2*(phi+q1))+ ... */
  /* 'CMatrix:371'   -c1*L*ml1*sin(2*phi+q1)-L*l1*ml2*sin(2*phi+q1)- ... */
  /* 'CMatrix:372'   c2*L*ml2*sin(q1+q2)+H2xx*sin(2*(phi+q1+q2))-H2yy*sin(2*( ... */
  /* 'CMatrix:373'   phi+q1+q2))-c2^2*ml2*sin(2*(phi+q1+q2))-c2*L*ml2*sin( ... */
  /* 'CMatrix:374'   2*phi+q1+q2)+(-2)*c2*l1*ml2*sin(2*(phi+q1)+q2))); */
  /* 'CMatrix:375' C56=(1/4)*(dq2*(c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2- ... */
  /* 'CMatrix:376'   th)+2*H2yz*cos(phi+q1+q2-th)+c2*L*ml2*cos(2*phi+q1+q2- ... */
  /* 'CMatrix:377'   th)+c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx*cos(2*phi+ ... */
  /* 'CMatrix:378'   2*q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+c2^2* ... */
  /* 'CMatrix:379'   ml2*cos(2*phi+2*q1+2*q2-th)+2*H2zz*cos(th)+2*c2^2*ml2* ... */
  /* 'CMatrix:380'   cos(th)+c2*l1*ml2*cos(q2+th)+c2*L*ml2*cos(q1+q2+th)+(-2)*H2yz* ... */
  /* 'CMatrix:381'   cos(phi+q1+q2+th)+c2*L*ml2*cos(2*phi+q1+q2+th)+c2*l1*ml2*cos(2* ... */
  /* 'CMatrix:382'   phi+2*q1+q2+th)-H2xx*cos(2*phi+2*q1+2*q2+th)+H2yy*cos(2* ... */
  /* 'CMatrix:383'   phi+2*q1+2*q2+th)+c2^2*ml2*cos(2*phi+2*q1+2*q2+th)+2*H2zx*sin( ... */
  /* 'CMatrix:384'   phi+q1+q2-th)+2*H2xy*sin(2*phi+2*q1+2*q2-th)+(-2)* ... */
  /* 'CMatrix:385'   H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+2*q2+th))+dq1*(L*( ... */
  /* 'CMatrix:386'   c1*ml1+l1*ml2)*cos(q1-th)+2*H1yz*cos(phi+q1-th)+c1*L* ... */
  /* 'CMatrix:387'   ml1*cos(2*phi+q1-th)+L*l1*ml2*cos(2*phi+q1-th)- ... */
  /* 'CMatrix:388'   H1xx*cos(2*phi+2*q1-th)+H1yy*cos(2*phi+2*q1-th)+ ... */
  /* 'CMatrix:389'   c1^2*ml1*cos(2*phi+2*q1-th)+l1^2*ml2*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:390'   *th)+2*c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2-th)+ ... */
  /* 'CMatrix:391'   2*H2yz*cos(phi+q1+q2-th)+c2*L*ml2*cos(2*phi+q1+q2-th)+ ... */
  /* 'CMatrix:392'   2*c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx*cos(2*phi+2* ... */
  /* 'CMatrix:393'   q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+c2^2*ml2* ... */
  /* 'CMatrix:394'   cos(2*phi+2*q1+2*q2-th)+2*H1zz*cos(th)+2*H2zz*cos(th)+2* ... */
  /* 'CMatrix:395'   c1^2*ml1*cos(th)+2*c2^2*ml2*cos(th)+2*l1^2*ml2*cos(th)+c1* ... */
  /* 'CMatrix:396'   L*ml1*cos(q1+th)+L*l1*ml2*cos(q1+th)+(-2)*H1yz*cos(phi+q1+th)+ ... */
  /* 'CMatrix:397'   c1*L*ml1*cos(2*phi+q1+th)+L*l1*ml2*cos(2*phi+q1+th)-H1xx* ... */
  /* 'CMatrix:398'   cos(2*phi+2*q1+th)+H1yy*cos(2*phi+2*q1+th)+c1^2*ml1*cos(2*phi+ ... */
  /* 'CMatrix:399'   2*q1+th)+l1^2*ml2*cos(2*phi+2*q1+th)+2*c2*l1*ml2*cos(q2+th)+ ... */
  /* 'CMatrix:400'   c2*L*ml2*cos(q1+q2+th)+(-2)*H2yz*cos(phi+q1+q2+th)+c2*L*ml2*cos( ... */
  /* 'CMatrix:401'   2*phi+q1+q2+th)+2*c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx* ... */
  /* 'CMatrix:402'   cos(2*phi+2*q1+2*q2+th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2* ... */
  /* 'CMatrix:403'   cos(2*phi+2*q1+2*q2+th)+2*H1zx*sin(phi+q1-th)+2*H1xy*sin( ... */
  /* 'CMatrix:404'   2*phi+2*q1-th)+2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2* ... */
  /* 'CMatrix:405'   phi+2*q1+2*q2-th)+(-2)*H1zx*sin(phi+q1+th)+2*H1xy*sin(2* ... */
  /* 'CMatrix:406'   phi+2*q1+th)+(-2)*H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+ ... */
  /* 'CMatrix:407'   2*q2+th))+dphi*((Hby-Hbz+L^2*(ml1+ml2))*cos(2*phi-th)+ ... */
  /* 'CMatrix:408'   2*L*(c1*ml1+l1*ml2)*cos(q1-th)+2*H1yz*cos(phi+q1-th)+ ... */
  /* 'CMatrix:409'   2*c1*L*ml1*cos(2*phi+q1-th)+2*L*l1*ml2*cos(2*phi+q1+(-1) ... */
  /* 'CMatrix:410'   *th)-H1xx*cos(2*phi+2*q1-th)+H1yy*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:411'   *th)+c1^2*ml1*cos(2*phi+2*q1-th)+l1^2*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:412'   q1-th)+2*c2*l1*ml2*cos(q2-th)+2*c2*L*ml2*cos(q1+q2+( ... */
  /* 'CMatrix:413'   -1)*th)+2*H2yz*cos(phi+q1+q2-th)+2*c2*L*ml2*cos(2*phi+q1+ ... */
  /* 'CMatrix:414'   q2-th)+2*c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx* ... */
  /* 'CMatrix:415'   cos(2*phi+2*q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:416'   c2^2*ml2*cos(2*phi+2*q1+2*q2-th)+2*H1zz*cos(th)+2*H2zz* ... */
  /* 'CMatrix:417'   cos(th)+2*Hbx*cos(th)+2*c1^2*ml1*cos(th)+2*L^2*ml1*cos(th)+2* ... */
  /* 'CMatrix:418'   c2^2*ml2*cos(th)+2*L^2*ml2*cos(th)+2*l1^2*ml2*cos(th)+Hby* ... */
  /* 'CMatrix:419'   cos(2*phi+th)-Hbz*cos(2*phi+th)+L^2*ml1*cos(2*phi+th)+ ... */
  /* 'CMatrix:420'   L^2*ml2*cos(2*phi+th)+2*c1*L*ml1*cos(q1+th)+2*L*l1*ml2*cos( ... */
  /* 'CMatrix:421'   q1+th)+(-2)*H1yz*cos(phi+q1+th)+2*c1*L*ml1*cos(2*phi+q1+th)+2* ... */
  /* 'CMatrix:422'   L*l1*ml2*cos(2*phi+q1+th)-H1xx*cos(2*phi+2*q1+th)+H1yy* ... */
  /* 'CMatrix:423'   cos(2*phi+2*q1+th)+c1^2*ml1*cos(2*phi+2*q1+th)+l1^2*ml2*cos( ... */
  /* 'CMatrix:424'   2*phi+2*q1+th)+2*c2*l1*ml2*cos(q2+th)+2*c2*L*ml2*cos(q1+q2+th) ... */
  /* 'CMatrix:425'   +(-2)*H2yz*cos(phi+q1+q2+th)+2*c2*L*ml2*cos(2*phi+q1+q2+th)+2* ... */
  /* 'CMatrix:426'   c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx*cos(2*phi+2*q1+2*q2+ ... */
  /* 'CMatrix:427'   th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2*cos(2*phi+2*q1+2*q2+ ... */
  /* 'CMatrix:428'   th)+2*H1zx*sin(phi+q1-th)+2*H1xy*sin(2*phi+2*q1-th)+ ... */
  /* 'CMatrix:429'   2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:430'   th)+(-2)*H1zx*sin(phi+q1+th)+2*H1xy*sin(2*phi+2*q1+th)+(-2)* ... */
  /* 'CMatrix:431'   H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+2*q2+th))+(-1/2)* ... */
  /* 'CMatrix:432'   dpsi*(4*H1zx*cos(phi+q1+(-2)*th)+4*H2zx*cos(phi+q1+q2+(-2)*th)+ ... */
  /* 'CMatrix:433'   2*H1xy*cos(2*(phi+q1-th))+2*H2xy*cos(2*(phi+q1+q2-th)) ... */
  /* 'CMatrix:434'   +(-2)*H1xy*cos(2*(phi+q1+th))+(-2)*H2xy*cos(2*(phi+q1+q2+th))+4* ... */
  /* 'CMatrix:435'   H1zx*cos(phi+q1+2*th)+4*H2zx*cos(phi+q1+q2+2*th)+(-2)*c2*l1* ... */
  /* 'CMatrix:436'   ml2*sin(q2+2*(phi+q1-th))+(-2)*c1*L*ml1*sin(q1+(-2)*th)+( ... */
  /* 'CMatrix:437'   -2)*L*l1*ml2*sin(q1+(-2)*th)+(-4)*H1yz*sin(phi+q1+(-2)*th)+(-2) ... */
  /* 'CMatrix:438'   *c1*L*ml1*sin(2*phi+q1+(-2)*th)+(-2)*L*l1*ml2*sin(2*phi+q1+( ... */
  /* 'CMatrix:439'   -2)*th)+(-2)*c2*l1*ml2*sin(q2+(-2)*th)+(-2)*c2*L*ml2*sin(q1+ ... */
  /* 'CMatrix:440'   q2+(-2)*th)+(-4)*H2yz*sin(phi+q1+q2+(-2)*th)+(-2)*c2*L*ml2*sin( ... */
  /* 'CMatrix:441'   2*phi+q1+q2+(-2)*th)+Hbz*sin(2*(phi-th))+H1xx*sin(2*(phi+q1+ ... */
  /* 'CMatrix:442'   -th))-H1yy*sin(2*(phi+q1-th))-c1^2*ml1*sin( ... */
  /* 'CMatrix:443'   2*(phi+q1-th))-l1^2*ml2*sin(2*(phi+q1-th))+H2xx* ... */
  /* 'CMatrix:444'   sin(2*(phi+q1+q2-th))-H2yy*sin(2*(phi+q1+q2-th))+( ... */
  /* 'CMatrix:445'   -1)*c2^2*ml2*sin(2*(phi+q1+q2-th))+(-2)*H1xx*sin(2*th)+( ... */
  /* 'CMatrix:446'   -2)*H1yy*sin(2*th)+4*H1zz*sin(2*th)+(-2)*H2xx*sin(2*th)+(-2)* ... */
  /* 'CMatrix:447'   H2yy*sin(2*th)+4*H2zz*sin(2*th)+4*Hbx*sin(2*th)+(-2)*Hby*sin( ... */
  /* 'CMatrix:448'   2*th)+(-2)*Hbz*sin(2*th)+2*c1^2*ml1*sin(2*th)+2*L^2*ml1* ... */
  /* 'CMatrix:449'   sin(2*th)+2*c2^2*ml2*sin(2*th)+2*L^2*ml2*sin(2*th)+2*l1^2* ... */
  /* 'CMatrix:450'   ml2*sin(2*th)+Hby*sin(2*(-phi+th))+L^2*ml1*sin(2*(- ... */
  /* 'CMatrix:451'   phi+th))+L^2*ml2*sin(2*(-phi+th))+Hby*sin(2*(phi+th))- ... */
  /* 'CMatrix:452'   Hbz*sin(2*(phi+th))+L^2*ml1*sin(2*(phi+th))+L^2*ml2*sin(2*( ... */
  /* 'CMatrix:453'   phi+th))-H1xx*sin(2*(phi+q1+th))+H1yy*sin(2*(phi+q1+th))+ ... */
  /* 'CMatrix:454'   c1^2*ml1*sin(2*(phi+q1+th))+l1^2*ml2*sin(2*(phi+q1+th))- ... */
  /* 'CMatrix:455'   H2xx*sin(2*(phi+q1+q2+th))+H2yy*sin(2*(phi+q1+q2+th))+c2^2*ml2* ... */
  /* 'CMatrix:456'   sin(2*(phi+q1+q2+th))+2*c1*L*ml1*sin(q1+2*th)+2*L*l1*ml2*sin( ... */
  /* 'CMatrix:457'   q1+2*th)+(-4)*H1yz*sin(phi+q1+2*th)+2*c2*l1*ml2*sin(q2+2*th)+ ... */
  /* 'CMatrix:458'   2*c2*L*ml2*sin(q1+q2+2*th)+(-4)*H2yz*sin(phi+q1+q2+2*th)+2*c1* ... */
  /* 'CMatrix:459'   L*ml1*sin(q1+2*(phi+th))+2*L*l1*ml2*sin(q1+2*(phi+th))+2*c2* ... */
  /* 'CMatrix:460'   L*ml2*sin(q1+q2+2*(phi+th))+2*c2*l1*ml2*sin(q2+2*(phi+q1+th)))); */
  /* 'CMatrix:462' C57=(1/4)*(4*(dphi+dq1)*H1zx*cos(phi+q1)+4*dth*H1xy*cos(2*(phi+q1))+ ... */
  /* 'CMatrix:463'   4*dphi*H2zx*cos(phi+q1+q2)+4*dq1*H2zx*cos(phi+q1+q2)+4*dq2* ... */
  /* 'CMatrix:464'   H2zx*cos(phi+q1+q2)+4*dth*H2xy*cos(2*(phi+q1+q2))+c1*dpsi*L* ... */
  /* 'CMatrix:465'   ml1*cos(q1-th)+dpsi*L*l1*ml2*cos(q1-th)+2*dpsi*H1yz* ... */
  /* 'CMatrix:466'   cos(phi+q1-th)+c1*dpsi*L*ml1*cos(2*phi+q1-th)+dpsi*L* ... */
  /* 'CMatrix:467'   l1*ml2*cos(2*phi+q1-th)-dpsi*H1xx*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:468'   *th)+dpsi*H1yy*cos(2*phi+2*q1-th)+c1^2*dpsi*ml1*cos(2* ... */
  /* 'CMatrix:469'   phi+2*q1-th)+dpsi*l1^2*ml2*cos(2*phi+2*q1-th)+2*c2* ... */
  /* 'CMatrix:470'   dpsi*l1*ml2*cos(q2-th)+c2*dpsi*L*ml2*cos(q1+q2-th)+ ... */
  /* 'CMatrix:471'   2*dpsi*H2yz*cos(phi+q1+q2-th)+c2*dpsi*L*ml2*cos(2*phi+q1+ ... */
  /* 'CMatrix:472'   q2-th)+2*c2*dpsi*l1*ml2*cos(2*phi+2*q1+q2-th)- ... */
  /* 'CMatrix:473'   dpsi*H2xx*cos(2*phi+2*q1+2*q2-th)+dpsi*H2yy*cos(2*phi+2* ... */
  /* 'CMatrix:474'   q1+2*q2-th)+c2^2*dpsi*ml2*cos(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:475'   2*dpsi*H1zz*cos(th)+2*dpsi*H2zz*cos(th)+2*c1^2*dpsi*ml1*cos( ... */
  /* 'CMatrix:476'   th)+2*c2^2*dpsi*ml2*cos(th)+2*dpsi*l1^2*ml2*cos(th)+c1*dpsi* ... */
  /* 'CMatrix:477'   L*ml1*cos(q1+th)+dpsi*L*l1*ml2*cos(q1+th)+(-2)*dpsi*H1yz*cos( ... */
  /* 'CMatrix:478'   phi+q1+th)+c1*dpsi*L*ml1*cos(2*phi+q1+th)+dpsi*L*l1*ml2*cos(2* ... */
  /* 'CMatrix:479'   phi+q1+th)-dpsi*H1xx*cos(2*phi+2*q1+th)+dpsi*H1yy*cos(2* ... */
  /* 'CMatrix:480'   phi+2*q1+th)+c1^2*dpsi*ml1*cos(2*phi+2*q1+th)+dpsi*l1^2*ml2* ... */
  /* 'CMatrix:481'   cos(2*phi+2*q1+th)+2*c2*dpsi*l1*ml2*cos(q2+th)+c2*dpsi*L*ml2* ... */
  /* 'CMatrix:482'   cos(q1+q2+th)+(-2)*dpsi*H2yz*cos(phi+q1+q2+th)+c2*dpsi*L*ml2*cos( ... */
  /* 'CMatrix:483'   2*phi+q1+q2+th)+2*c2*dpsi*l1*ml2*cos(2*phi+2*q1+q2+th)- ... */
  /* 'CMatrix:484'   dpsi*H2xx*cos(2*phi+2*q1+2*q2+th)+dpsi*H2yy*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:485'   q2+th)+c2^2*dpsi*ml2*cos(2*phi+2*q1+2*q2+th)+(-2)*c1*dth*L* ... */
  /* 'CMatrix:486'   ml1*sin(q1)+(-2)*dth*L*l1*ml2*sin(q1)+(-4)*dphi*H1yz*sin(phi+ ... */
  /* 'CMatrix:487'   q1)+(-4)*dq1*H1yz*sin(phi+q1)+2*dth*H1xx*sin(2*(phi+q1))+(-2)* ... */
  /* 'CMatrix:488'   dth*H1yy*sin(2*(phi+q1))+(-2)*c1^2*dth*ml1*sin(2*(phi+q1))+(-2) ... */
  /* 'CMatrix:489'   *dth*l1^2*ml2*sin(2*(phi+q1))+(-2)*c1*dth*L*ml1*sin(2*phi+ ... */
  /* 'CMatrix:490'   q1)+(-2)*dth*L*l1*ml2*sin(2*phi+q1)+(-2)*c2*dth*L*ml2*sin(q1+ ... */
  /* 'CMatrix:491'   q2)+(-4)*dphi*H2yz*sin(phi+q1+q2)+(-4)*dq1*H2yz*sin(phi+q1+q2)+( ... */
  /* 'CMatrix:492'   -4)*dq2*H2yz*sin(phi+q1+q2)+2*dth*H2xx*sin(2*(phi+q1+q2))+(-2)* ... */
  /* 'CMatrix:493'   dth*H2yy*sin(2*(phi+q1+q2))+(-2)*c2^2*dth*ml2*sin(2*(phi+q1+q2) ... */
  /* 'CMatrix:494'   )+(-2)*c2*dth*L*ml2*sin(2*phi+q1+q2)+(-4)*c2*dth*l1*ml2*sin( ... */
  /* 'CMatrix:495'   2*(phi+q1)+q2)+2*dpsi*H1zx*sin(phi+q1-th)+2*dpsi*H1xy*sin( ... */
  /* 'CMatrix:496'   2*phi+2*q1-th)+2*dpsi*H2zx*sin(phi+q1+q2-th)+2*dpsi* ... */
  /* 'CMatrix:497'   H2xy*sin(2*phi+2*q1+2*q2-th)+(-2)*dpsi*H1zx*sin(phi+q1+th)+ ... */
  /* 'CMatrix:498'   2*dpsi*H1xy*sin(2*phi+2*q1+th)+(-2)*dpsi*H2zx*sin(phi+q1+q2+th)+ ... */
  /* 'CMatrix:499'   2*dpsi*H2xy*sin(2*phi+2*q1+2*q2+th)); */
  /* 'CMatrix:500' C58=(1/4)*(4*(dphi+dq1+dq2)*H2zx*cos(phi+q1+q2)+4*dth*H2xy*cos(2*( ... */
  /* 'CMatrix:501'   phi+q1+q2))+c2*dpsi*l1*ml2*cos(q2-th)+c2*dpsi*L*ml2*cos( ... */
  /* 'CMatrix:502'   q1+q2-th)+2*dpsi*H2yz*cos(phi+q1+q2-th)+c2*dpsi*L* ... */
  /* 'CMatrix:503'   ml2*cos(2*phi+q1+q2-th)+c2*dpsi*l1*ml2*cos(2*phi+2*q1+q2+( ... */
  /* 'CMatrix:504'   -1)*th)-dpsi*H2xx*cos(2*phi+2*q1+2*q2-th)+dpsi*H2yy* ... */
  /* 'CMatrix:505'   cos(2*phi+2*q1+2*q2-th)+c2^2*dpsi*ml2*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:506'   q2-th)+2*dpsi*H2zz*cos(th)+2*c2^2*dpsi*ml2*cos(th)+c2* ... */
  /* 'CMatrix:507'   dpsi*l1*ml2*cos(q2+th)+c2*dpsi*L*ml2*cos(q1+q2+th)+(-2)*dpsi* ... */
  /* 'CMatrix:508'   H2yz*cos(phi+q1+q2+th)+c2*dpsi*L*ml2*cos(2*phi+q1+q2+th)+c2* ... */
  /* 'CMatrix:509'   dpsi*l1*ml2*cos(2*phi+2*q1+q2+th)-dpsi*H2xx*cos(2*phi+2* ... */
  /* 'CMatrix:510'   q1+2*q2+th)+dpsi*H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*dpsi*ml2* ... */
  /* 'CMatrix:511'   cos(2*phi+2*q1+2*q2+th)+(-2)*c2*dth*l1*ml2*sin(q2)+(-2)*c2* ... */
  /* 'CMatrix:512'   dth*L*ml2*sin(q1+q2)+(-4)*dphi*H2yz*sin(phi+q1+q2)+(-4)*dq1* ... */
  /* 'CMatrix:513'   H2yz*sin(phi+q1+q2)+(-4)*dq2*H2yz*sin(phi+q1+q2)+2*dth*H2xx*sin( ... */
  /* 'CMatrix:514'   2*(phi+q1+q2))+(-2)*dth*H2yy*sin(2*(phi+q1+q2))+(-2)*c2^2*dth* ... */
  /* 'CMatrix:515'   ml2*sin(2*(phi+q1+q2))+(-2)*c2*dth*L*ml2*sin(2*phi+q1+q2)+(-2)* ... */
  /* 'CMatrix:516'   c2*dth*l1*ml2*sin(2*(phi+q1)+q2)+2*dpsi*H2zx*sin(phi+q1+q2+(-1) ... */
  /* 'CMatrix:517'   *th)+2*dpsi*H2xy*sin(2*phi+2*q1+2*q2-th)+(-2)*dpsi*H2zx* ... */
  /* 'CMatrix:518'   sin(phi+q1+q2+th)+2*dpsi*H2xy*sin(2*phi+2*q1+2*q2+th)); */
  /* 'CMatrix:41' [C64, C65, C66, C67, C68] = get_C6(); */
  /* 'CMatrix:522' C64=(1/4)*(2*dq2*(c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2+( ... */
  /* 'CMatrix:523'   -1)*th)+H2yz*cos(phi+q1+q2-th)-c2*l1*ml2*cos(q2+th)+( ... */
  /* 'CMatrix:524'   -1)*c2*L*ml2*cos(q1+q2+th)+H2yz*cos(phi+q1+q2+th)+H2zx*sin(phi+q1+ ... */
  /* 'CMatrix:525'   q2-th)+H2zx*sin(phi+q1+q2+th))+2*dq1*(L*(c1*ml1+l1*ml2)* ... */
  /* 'CMatrix:526'   cos(q1-th)+H1yz*cos(phi+q1-th)+c2*L*ml2*cos(q1+q2- ... */
  /* 'CMatrix:527'   th)+H2yz*cos(phi+q1+q2-th)-c1*L*ml1*cos(q1+th)-L* ... */
  /* 'CMatrix:528'   l1*ml2*cos(q1+th)+H1yz*cos(phi+q1+th)-c2*L*ml2*cos(q1+q2+th) ... */
  /* 'CMatrix:529'   +H2yz*cos(phi+q1+q2+th)+H1zx*sin(phi+q1-th)+H2zx*sin(phi+q1+q2+ ... */
  /* 'CMatrix:530'   -th)+H1zx*sin(phi+q1+th)+H2zx*sin(phi+q1+q2+th))+cos(th)*(4* ... */
  /* 'CMatrix:531'   dphi*(H1yz*cos(phi+q1)+H2yz*cos(phi+q1+q2)+H1zx*sin(phi+q1)+H2zx* ... */
  /* 'CMatrix:532'   sin(phi+q1+q2))+(-2)*dth*(H1zz+H2zz+Hbx+c1^2*ml1+L^2*ml1+c2^2* ... */
  /* 'CMatrix:533'   ml2+L^2*ml2+l1^2*ml2-(Hby-Hbz+L^2*(ml1+ml2))*cos(2* ... */
  /* 'CMatrix:534'   phi)+2*L*(c1*ml1+l1*ml2)*cos(q1)+H1xx*cos(2*(phi+q1))- ... */
  /* 'CMatrix:535'   H1yy*cos(2*(phi+q1))-c1^2*ml1*cos(2*(phi+q1))-l1^2* ... */
  /* 'CMatrix:536'   ml2*cos(2*(phi+q1))+(-2)*c1*L*ml1*cos(2*phi+q1)+(-2)*L*l1* ... */
  /* 'CMatrix:537'   ml2*cos(2*phi+q1)+2*c2*l1*ml2*cos(q2)+2*c2*L*ml2*cos(q1+q2)+ ... */
  /* 'CMatrix:538'   H2xx*cos(2*(phi+q1+q2))-H2yy*cos(2*(phi+q1+q2))-c2^2* ... */
  /* 'CMatrix:539'   ml2*cos(2*(phi+q1+q2))+(-2)*c2*L*ml2*cos(2*phi+q1+q2)+(-2)*c2* ... */
  /* 'CMatrix:540'   l1*ml2*cos(2*(phi+q1)+q2)+(-2)*H1xy*sin(2*(phi+q1))+(-2)*H2xy* ... */
  /* 'CMatrix:541'   sin(2*(phi+q1+q2)))+dpsi*((-2)*H1zx*cos(phi+q1-th)+(-2)* ... */
  /* 'CMatrix:542'   H1xy*cos(2*phi+2*q1-th)+(-2)*H2zx*cos(phi+q1+q2-th)+( ... */
  /* 'CMatrix:543'   -2)*H2xy*cos(2*phi+2*q1+2*q2-th)+2*H1zx*cos(phi+q1+th)+(-2) ... */
  /* 'CMatrix:544'   *H1xy*cos(2*phi+2*q1+th)+2*H2zx*cos(phi+q1+q2+th)+(-2)*H2xy*cos( ... */
  /* 'CMatrix:545'   2*phi+2*q1+2*q2+th)+Hby*sin(2*phi-th)-Hbz*sin(2*phi+( ... */
  /* 'CMatrix:546'   -1)*th)+L^2*ml1*sin(2*phi-th)+L^2*ml2*sin(2*phi-th) ... */
  /* 'CMatrix:547'   +2*H1yz*sin(phi+q1-th)+2*c1*L*ml1*sin(2*phi+q1-th)+ ... */
  /* 'CMatrix:548'   2*L*l1*ml2*sin(2*phi+q1-th)-H1xx*sin(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:549'   *th)+H1yy*sin(2*phi+2*q1-th)+c1^2*ml1*sin(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:550'   *th)+l1^2*ml2*sin(2*phi+2*q1-th)+2*H2yz*sin(phi+q1+q2+(-1) ... */
  /* 'CMatrix:551'   *th)+2*c2*L*ml2*sin(2*phi+q1+q2-th)+2*c2*l1*ml2*sin(2* ... */
  /* 'CMatrix:552'   phi+2*q1+q2-th)-H2xx*sin(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:553'   H2yy*sin(2*phi+2*q1+2*q2-th)+c2^2*ml2*sin(2*phi+2*q1+2* ... */
  /* 'CMatrix:554'   q2-th)+Hby*sin(2*phi+th)-Hbz*sin(2*phi+th)+L^2*ml1* ... */
  /* 'CMatrix:555'   sin(2*phi+th)+L^2*ml2*sin(2*phi+th)+(-2)*H1yz*sin(phi+q1+th)+2* ... */
  /* 'CMatrix:556'   c1*L*ml1*sin(2*phi+q1+th)+2*L*l1*ml2*sin(2*phi+q1+th)- ... */
  /* 'CMatrix:557'   H1xx*sin(2*phi+2*q1+th)+H1yy*sin(2*phi+2*q1+th)+c1^2*ml1*sin( ... */
  /* 'CMatrix:558'   2*phi+2*q1+th)+l1^2*ml2*sin(2*phi+2*q1+th)+(-2)*H2yz*sin(phi+ ... */
  /* 'CMatrix:559'   q1+q2+th)+2*c2*L*ml2*sin(2*phi+q1+q2+th)+2*c2*l1*ml2*sin(2* ... */
  /* 'CMatrix:560'   phi+2*q1+q2+th)-H2xx*sin(2*phi+2*q1+2*q2+th)+H2yy*sin(2* ... */
  /* 'CMatrix:561'   phi+2*q1+2*q2+th)+c2^2*ml2*sin(2*phi+2*q1+2*q2+th)))); */
  /* 'CMatrix:562' C65=(1/8)*(4*dpsi*H1zx*cos(phi+q1+(-2)*th)+4*dpsi*H2zx*cos(phi+q1+ ... */
  /* 'CMatrix:563'   q2+(-2)*th)+2*dphi*Hby*cos(2*phi-th)+(-2)*dth*Hby*cos(2* ... */
  /* 'CMatrix:564'   phi-th)+(-2)*dphi*Hbz*cos(2*phi-th)+2*dth*Hbz*cos(2* ... */
  /* 'CMatrix:565'   phi-th)+2*dphi*L^2*ml1*cos(2*phi-th)+(-2)*dth*L^2* ... */
  /* 'CMatrix:566'   ml1*cos(2*phi-th)+2*dphi*L^2*ml2*cos(2*phi-th)+(-2) ... */
  /* 'CMatrix:567'   *dth*L^2*ml2*cos(2*phi-th)+(-4)*c1*dphi*L*ml1*cos(q1+( ... */
  /* 'CMatrix:568'   -1)*th)+(-4)*dphi*L*l1*ml2*cos(q1-th)+(-4)*dth*H1yz*cos( ... */
  /* 'CMatrix:569'   phi+q1-th)+2*dpsi*H1xy*cos(2*(phi+q1-th))+4*c1*dphi* ... */
  /* 'CMatrix:570'   L*ml1*cos(2*phi+q1-th)+(-4)*c1*dth*L*ml1*cos(2*phi+q1+( ... */
  /* 'CMatrix:571'   -1)*th)+4*dphi*L*l1*ml2*cos(2*phi+q1-th)+(-4)*dth*L*l1* ... */
  /* 'CMatrix:572'   ml2*cos(2*phi+q1-th)+(-2)*dphi*H1xx*cos(2*phi+2*q1- ... */
  /* 'CMatrix:573'   th)+2*dth*H1xx*cos(2*phi+2*q1-th)+2*dphi*H1yy*cos(2*phi+ ... */
  /* 'CMatrix:574'   2*q1-th)+(-2)*dth*H1yy*cos(2*phi+2*q1-th)+2*c1^2* ... */
  /* 'CMatrix:575'   dphi*ml1*cos(2*phi+2*q1-th)+(-2)*c1^2*dth*ml1*cos(2*phi+ ... */
  /* 'CMatrix:576'   2*q1-th)+2*dphi*l1^2*ml2*cos(2*phi+2*q1-th)+(-2)* ... */
  /* 'CMatrix:577'   dth*l1^2*ml2*cos(2*phi+2*q1-th)+(-4)*c2*dphi*l1*ml2* ... */
  /* 'CMatrix:578'   cos(q2-th)+(-4)*c2*dphi*L*ml2*cos(q1+q2-th)+(-4)*dth* ... */
  /* 'CMatrix:579'   H2yz*cos(phi+q1+q2-th)+2*dpsi*H2xy*cos(2*(phi+q1+q2-th) ... */
  /* 'CMatrix:580'   )+4*c2*dphi*L*ml2*cos(2*phi+q1+q2-th)+(-4)*c2*dth*L* ... */
  /* 'CMatrix:581'   ml2*cos(2*phi+q1+q2-th)+4*c2*dphi*l1*ml2*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:582'   q2-th)+(-4)*c2*dth*l1*ml2*cos(2*phi+2*q1+q2-th)+(-2) ... */
  /* 'CMatrix:583'   *dphi*H2xx*cos(2*phi+2*q1+2*q2-th)+2*dth*H2xx*cos(2*phi+ ... */
  /* 'CMatrix:584'   2*q1+2*q2-th)+2*dphi*H2yy*cos(2*phi+2*q1+2*q2-th)+( ... */
  /* 'CMatrix:585'   -2)*dth*H2yy*cos(2*phi+2*q1+2*q2-th)+2*c2^2*dphi*ml2* ... */
  /* 'CMatrix:586'   cos(2*phi+2*q1+2*q2-th)+(-2)*c2^2*dth*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:587'   q1+2*q2-th)+(-4)*dphi*H1zz*cos(th)+(-4)*dphi*H2zz*cos(th)+( ... */
  /* 'CMatrix:588'   -4)*dphi*Hbx*cos(th)+(-4)*c1^2*dphi*ml1*cos(th)+(-4)*dphi* ... */
  /* 'CMatrix:589'   L^2*ml1*cos(th)+(-4)*c2^2*dphi*ml2*cos(th)+(-4)*dphi*L^2* ... */
  /* 'CMatrix:590'   ml2*cos(th)+(-4)*dphi*l1^2*ml2*cos(th)+2*dphi*Hby*cos(2*phi+ ... */
  /* 'CMatrix:591'   th)+2*dth*Hby*cos(2*phi+th)+(-2)*dphi*Hbz*cos(2*phi+th)+(-2)* ... */
  /* 'CMatrix:592'   dth*Hbz*cos(2*phi+th)+2*dphi*L^2*ml1*cos(2*phi+th)+2*dth* ... */
  /* 'CMatrix:593'   L^2*ml1*cos(2*phi+th)+2*dphi*L^2*ml2*cos(2*phi+th)+2*dth* ... */
  /* 'CMatrix:594'   L^2*ml2*cos(2*phi+th)+(-4)*c1*dphi*L*ml1*cos(q1+th)+(-4)* ... */
  /* 'CMatrix:595'   dphi*L*l1*ml2*cos(q1+th)+(-4)*dth*H1yz*cos(phi+q1+th)+(-2)* ... */
  /* 'CMatrix:596'   dpsi*H1xy*cos(2*(phi+q1+th))+4*c1*dphi*L*ml1*cos(2*phi+q1+th)+ ... */
  /* 'CMatrix:597'   4*c1*dth*L*ml1*cos(2*phi+q1+th)+4*dphi*L*l1*ml2*cos(2*phi+ ... */
  /* 'CMatrix:598'   q1+th)+4*dth*L*l1*ml2*cos(2*phi+q1+th)+(-2)*dphi*H1xx*cos(2* ... */
  /* 'CMatrix:599'   phi+2*q1+th)+(-2)*dth*H1xx*cos(2*phi+2*q1+th)+2*dphi*H1yy*cos( ... */
  /* 'CMatrix:600'   2*phi+2*q1+th)+2*dth*H1yy*cos(2*phi+2*q1+th)+2*c1^2*dphi* ... */
  /* 'CMatrix:601'   ml1*cos(2*phi+2*q1+th)+2*c1^2*dth*ml1*cos(2*phi+2*q1+th)+2* ... */
  /* 'CMatrix:602'   dphi*l1^2*ml2*cos(2*phi+2*q1+th)+2*dth*l1^2*ml2*cos(2*phi+ ... */
  /* 'CMatrix:603'   2*q1+th)+(-4)*c2*dphi*l1*ml2*cos(q2+th)+(-4)*c2*dphi*L*ml2* ... */
  /* 'CMatrix:604'   cos(q1+q2+th)+(-4)*dth*H2yz*cos(phi+q1+q2+th)+(-2)*dpsi*H2xy*cos( ... */
  /* 'CMatrix:605'   2*(phi+q1+q2+th))+4*c2*dphi*L*ml2*cos(2*phi+q1+q2+th)+4*c2* ... */
  /* 'CMatrix:606'   dth*L*ml2*cos(2*phi+q1+q2+th)+4*c2*dphi*l1*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:607'   q1+q2+th)+4*c2*dth*l1*ml2*cos(2*phi+2*q1+q2+th)+(-2)*dphi* ... */
  /* 'CMatrix:608'   H2xx*cos(2*phi+2*q1+2*q2+th)+(-2)*dth*H2xx*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:609'   q2+th)+2*dphi*H2yy*cos(2*phi+2*q1+2*q2+th)+2*dth*H2yy*cos(2* ... */
  /* 'CMatrix:610'   phi+2*q1+2*q2+th)+2*c2^2*dphi*ml2*cos(2*phi+2*q1+2*q2+th)+2* ... */
  /* 'CMatrix:611'   c2^2*dth*ml2*cos(2*phi+2*q1+2*q2+th)+4*dpsi*H1zx*cos(phi+q1+ ... */
  /* 'CMatrix:612'   2*th)+4*dpsi*H2zx*cos(phi+q1+q2+2*th)+(-4)*dq2*cos(th)*(H2zz+ ... */
  /* 'CMatrix:613'   c2^2*ml2+c2*l1*ml2*cos(q2)+c2*L*ml2*cos(q1+q2)+H2xx*cos(2*( ... */
  /* 'CMatrix:614'   phi+q1+q2))-H2yy*cos(2*(phi+q1+q2))-c2^2*ml2*cos(2*( ... */
  /* 'CMatrix:615'   phi+q1+q2))-c2*L*ml2*cos(2*phi+q1+q2)-c2*l1*ml2*cos( ... */
  /* 'CMatrix:616'   2*(phi+q1)+q2)+(-2)*H2xy*sin(2*(phi+q1+q2)))+(-4)*dq1*cos(th)*( ... */
  /* 'CMatrix:617'   H1zz+H2zz+c1^2*ml1+c2^2*ml2+l1^2*ml2+L*(c1*ml1+l1*ml2)*cos(q1) ... */
  /* 'CMatrix:618'   +(H1xx-H1yy-c1^2*ml1-l1^2*ml2)*cos(2*(phi+q1))+( ... */
  /* 'CMatrix:619'   -1)*c1*L*ml1*cos(2*phi+q1)-L*l1*ml2*cos(2*phi+q1)+2*c2* ... */
  /* 'CMatrix:620'   l1*ml2*cos(q2)+c2*L*ml2*cos(q1+q2)+H2xx*cos(2*(phi+q1+q2))- ... */
  /* 'CMatrix:621'   H2yy*cos(2*(phi+q1+q2))-c2^2*ml2*cos(2*(phi+q1+q2))- ... */
  /* 'CMatrix:622'   c2*L*ml2*cos(2*phi+q1+q2)+(-2)*c2*l1*ml2*cos(2*(phi+q1)+q2)+( ... */
  /* 'CMatrix:623'   -2)*H1xy*sin(2*(phi+q1))+(-2)*H2xy*sin(2*(phi+q1+q2)))+(-2)*c2* ... */
  /* 'CMatrix:624'   dpsi*l1*ml2*sin(q2+2*(phi+q1-th))+(-2)*c1*dpsi*L*ml1*sin( ... */
  /* 'CMatrix:625'   q1+(-2)*th)+(-2)*dpsi*L*l1*ml2*sin(q1+(-2)*th)+(-4)*dpsi*H1yz* ... */
  /* 'CMatrix:626'   sin(phi+q1+(-2)*th)+(-2)*c1*dpsi*L*ml1*sin(2*phi+q1+(-2)*th)+( ... */
  /* 'CMatrix:627'   -2)*dpsi*L*l1*ml2*sin(2*phi+q1+(-2)*th)+(-2)*c2*dpsi*l1*ml2* ... */
  /* 'CMatrix:628'   sin(q2+(-2)*th)+(-2)*c2*dpsi*L*ml2*sin(q1+q2+(-2)*th)+(-4)* ... */
  /* 'CMatrix:629'   dpsi*H2yz*sin(phi+q1+q2+(-2)*th)+(-2)*c2*dpsi*L*ml2*sin(2*phi+ ... */
  /* 'CMatrix:630'   q1+q2+(-2)*th)+dpsi*Hbz*sin(2*(phi-th))+(-4)*dth*H1zx*sin( ... */
  /* 'CMatrix:631'   phi+q1-th)+dpsi*H1xx*sin(2*(phi+q1-th))-dpsi* ... */
  /* 'CMatrix:632'   H1yy*sin(2*(phi+q1-th))-c1^2*dpsi*ml1*sin(2*(phi+q1+( ... */
  /* 'CMatrix:633'   -1)*th))-dpsi*l1^2*ml2*sin(2*(phi+q1-th))+4*dphi* ... */
  /* 'CMatrix:634'   H1xy*sin(2*phi+2*q1-th)+(-4)*dth*H1xy*sin(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:635'   *th)+(-4)*dth*H2zx*sin(phi+q1+q2-th)+dpsi*H2xx*sin(2*(phi+ ... */
  /* 'CMatrix:636'   q1+q2-th))-dpsi*H2yy*sin(2*(phi+q1+q2-th))- ... */
  /* 'CMatrix:637'   c2^2*dpsi*ml2*sin(2*(phi+q1+q2-th))+4*dphi*H2xy*sin(2* ... */
  /* 'CMatrix:638'   phi+2*q1+2*q2-th)+(-4)*dth*H2xy*sin(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:639'   th)+(-2)*dpsi*H1xx*sin(2*th)+(-2)*dpsi*H1yy*sin(2*th)+4*dpsi* ... */
  /* 'CMatrix:640'   H1zz*sin(2*th)+(-2)*dpsi*H2xx*sin(2*th)+(-2)*dpsi*H2yy*sin(2* ... */
  /* 'CMatrix:641'   th)+4*dpsi*H2zz*sin(2*th)+4*dpsi*Hbx*sin(2*th)+(-2)*dpsi*Hby* ... */
  /* 'CMatrix:642'   sin(2*th)+(-2)*dpsi*Hbz*sin(2*th)+2*c1^2*dpsi*ml1*sin(2*th)+ ... */
  /* 'CMatrix:643'   2*dpsi*L^2*ml1*sin(2*th)+2*c2^2*dpsi*ml2*sin(2*th)+2*dpsi* ... */
  /* 'CMatrix:644'   L^2*ml2*sin(2*th)+2*dpsi*l1^2*ml2*sin(2*th)+dpsi*Hby*sin(2* ... */
  /* 'CMatrix:645'   (-phi+th))+dpsi*L^2*ml1*sin(2*(-phi+th))+dpsi*L^2* ... */
  /* 'CMatrix:646'   ml2*sin(2*(-phi+th))+dpsi*Hby*sin(2*(phi+th))-dpsi* ... */
  /* 'CMatrix:647'   Hbz*sin(2*(phi+th))+dpsi*L^2*ml1*sin(2*(phi+th))+dpsi*L^2* ... */
  /* 'CMatrix:648'   ml2*sin(2*(phi+th))+(-4)*dth*H1zx*sin(phi+q1+th)-dpsi*H1xx* ... */
  /* 'CMatrix:649'   sin(2*(phi+q1+th))+dpsi*H1yy*sin(2*(phi+q1+th))+c1^2*dpsi*ml1* ... */
  /* 'CMatrix:650'   sin(2*(phi+q1+th))+dpsi*l1^2*ml2*sin(2*(phi+q1+th))+4*dphi* ... */
  /* 'CMatrix:651'   H1xy*sin(2*phi+2*q1+th)+4*dth*H1xy*sin(2*phi+2*q1+th)+(-4)* ... */
  /* 'CMatrix:652'   dth*H2zx*sin(phi+q1+q2+th)-dpsi*H2xx*sin(2*(phi+q1+q2+th))+ ... */
  /* 'CMatrix:653'   dpsi*H2yy*sin(2*(phi+q1+q2+th))+c2^2*dpsi*ml2*sin(2*(phi+q1+q2+ ... */
  /* 'CMatrix:654'   th))+4*dphi*H2xy*sin(2*phi+2*q1+2*q2+th)+4*dth*H2xy*sin(2*phi+ ... */
  /* 'CMatrix:655'   2*q1+2*q2+th)+2*c1*dpsi*L*ml1*sin(q1+2*th)+2*dpsi*L*l1*ml2* ... */
  /* 'CMatrix:656'   sin(q1+2*th)+(-4)*dpsi*H1yz*sin(phi+q1+2*th)+2*c2*dpsi*l1*ml2* ... */
  /* 'CMatrix:657'   sin(q2+2*th)+2*c2*dpsi*L*ml2*sin(q1+q2+2*th)+(-4)*dpsi*H2yz* ... */
  /* 'CMatrix:658'   sin(phi+q1+q2+2*th)+2*c1*dpsi*L*ml1*sin(q1+2*(phi+th))+2*dpsi* ... */
  /* 'CMatrix:659'   L*l1*ml2*sin(q1+2*(phi+th))+2*c2*dpsi*L*ml2*sin(q1+q2+2*(phi+ ... */
  /* 'CMatrix:660'   th))+2*c2*dpsi*l1*ml2*sin(q2+2*(phi+q1+th))); */
  /* 'CMatrix:661' C66=(1/4)*(2*dth*(2*cos(phi)*cos(2*th)*(H1zx*cos(q1)-H1yz* ... */
  /* 'CMatrix:662'   sin(q1))+(-2)*cos(2*th)*sin(phi)*(H1yz*cos(q1)+H1zx*sin(q1))+2* ... */
  /* 'CMatrix:663'   cos(phi)*cos(2*th)*(H2zx*cos(q1+q2)-H2yz*sin(q1+q2))+(-2)* ... */
  /* 'CMatrix:664'   cos(2*th)*sin(phi)*(H2yz*cos(q1+q2)+H2zx*sin(q1+q2))+4*cos(phi)* ... */
  /* 'CMatrix:665'   cos(th)*sin(phi)*(H1xy*cos(2*q1)+(H1xx-H1yy)*cos(q1)*sin(q1) ... */
  /* 'CMatrix:666'   )*sin(th)+(-2)*cos(phi)^2*cos(th)*(H1xx*cos(q1)^2+(-2)*H1xy* ... */
  /* 'CMatrix:667'   cos(q1)*sin(q1)+H1yy*sin(q1)^2)*sin(th)+(-2)*cos(th)*sin(phi)^2* ... */
  /* 'CMatrix:668'   (H1yy*cos(q1)^2+H1xx*sin(q1)^2+H1xy*sin(2*q1))*sin(th)-cos( ... */
  /* 'CMatrix:669'   phi)^2*cos(th)*(H2xx+H2yy+(H2xx-H2yy)*cos(2*(q1+q2))+(-2)* ... */
  /* 'CMatrix:670'   H2xy*sin(2*(q1+q2)))*sin(th)-cos(th)*sin(phi)^2*(H2xx+H2yy+( ... */
  /* 'CMatrix:671'   -H2xx+H2yy)*cos(2*(q1+q2))+2*H2xy*sin(2*(q1+q2)))*sin(th)+2* ... */
  /* 'CMatrix:672'   cos(phi)*cos(th)*sin(phi)*(2*H2xy*cos(2*(q1+q2))+(H2xx-H2yy) ... */
  /* 'CMatrix:673'   *sin(2*(q1+q2)))*sin(th)+(-2)*ml1*(L*cos(phi)+c1*cos(phi+q1))* ... */
  /* 'CMatrix:674'   cos(th)*sin(psi)*(cos(psi)*(L*sin(phi)+c1*sin(phi+q1))-(L* ... */
  /* 'CMatrix:675'   cos(phi)+c1*cos(phi+q1))*sin(psi)*sin(th))+(-2)*ml2*(L*cos(phi)+ ... */
  /* 'CMatrix:676'   l1*cos(phi+q1)+c2*cos(phi+q1+q2))*cos(th)*sin(psi)*(cos(psi)*(L* ... */
  /* 'CMatrix:677'   sin(phi)+l1*sin(phi+q1)+c2*sin(phi+q1+q2))-(L*cos(phi)+l1*cos( ... */
  /* 'CMatrix:678'   phi+q1)+c2*cos(phi+q1+q2))*sin(psi)*sin(th))+(-2)*ml1*cos(psi)*( ... */
  /* 'CMatrix:679'   L*cos(phi)+c1*cos(phi+q1))*cos(th)*(-(L+c1*cos(q1))*(sin(phi) ... */
  /* 'CMatrix:680'   *sin(psi)+cos(phi)*cos(psi)*sin(th))+c1*sin(q1)*(-cos(phi)* ... */
  /* 'CMatrix:681'   sin(psi)+cos(psi)*sin(phi)*sin(th)))+(-2)*ml2*cos(psi)*(L*cos(phi) ... */
  /* 'CMatrix:682'   +l1*cos(phi+q1)+c2*cos(phi+q1+q2))*cos(th)*(-(L+l1*cos(q1)+ ... */
  /* 'CMatrix:683'   c2*cos(q1+q2))*(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))+(l1* ... */
  /* 'CMatrix:684'   sin(q1)+c2*sin(q1+q2))*(-cos(phi)*sin(psi)+cos(psi)*sin(phi)* ... */
  /* 'CMatrix:685'   sin(th)))+H1zz*sin(2*th)+H2zz*sin(2*th)+Hbx*sin(2*th)-Hbz* ... */
  /* 'CMatrix:686'   cos(phi)^2*sin(2*th)-Hby*sin(phi)^2*sin(2*th))+dq2*(4* ... */
  /* 'CMatrix:687'   cos(phi)*cos(th)^2*sin(phi)*((-H2xx+H2yy)*cos(2*(q1+q2))+2* ... */
  /* 'CMatrix:688'   H2xy*sin(2*(q1+q2)))+cos(th)^2*sin(phi)^2*(4*H2xy*cos(2*(q1+q2) ... */
  /* 'CMatrix:689'   )+2*(H2xx-H2yy)*sin(2*(q1+q2)))+cos(phi)^2*cos(th)^2*((-4) ... */
  /* 'CMatrix:690'   *H2xy*cos(2*(q1+q2))+2*(-H2xx+H2yy)*sin(2*(q1+q2)))+4*ml2*( ... */
  /* 'CMatrix:691'   c2*sin(q1+q2)*(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))+c2* ... */
  /* 'CMatrix:692'   cos(q1+q2)*(-cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th)))*(( ... */
  /* 'CMatrix:693'   -1)*(L+l1*cos(q1)+c2*cos(q1+q2))*(sin(phi)*sin(psi)+cos(phi)*cos( ... */
  /* 'CMatrix:694'   psi)*sin(th))+(l1*sin(q1)+c2*sin(q1+q2))*(-cos(phi)*sin(psi)+ ... */
  /* 'CMatrix:695'   cos(psi)*sin(phi)*sin(th)))+4*ml2*(cos(psi)*(L*sin(phi)+l1*sin( ... */
  /* 'CMatrix:696'   phi+q1)+c2*sin(phi+q1+q2))-(L*cos(phi)+l1*cos(phi+q1)+c2*cos( ... */
  /* 'CMatrix:697'   phi+q1+q2))*sin(psi)*sin(th))*(c2*sin(q1+q2)*(-cos(psi)*sin( ... */
  /* 'CMatrix:698'   phi)+cos(phi)*sin(psi)*sin(th))+c2*cos(q1+q2)*(cos(phi)*cos(psi)+ ... */
  /* 'CMatrix:699'   sin(phi)*sin(psi)*sin(th)))+(-2)*sin(phi)*(H2zx*cos(q1+q2)- ... */
  /* 'CMatrix:700'   H2yz*sin(q1+q2))*sin(2*th)+(-2)*cos(phi)*(H2yz*cos(q1+q2)+H2zx* ... */
  /* 'CMatrix:701'   sin(q1+q2))*sin(2*th))+dq1*((-2)*cos(th)^2*sin(2*phi)*((H1xx+( ... */
  /* 'CMatrix:702'   -1)*H1yy)*cos(2*q1)+(-2)*H1xy*sin(2*q1))+(-2)*cos(phi)^2*cos( ... */
  /* 'CMatrix:703'   th)^2*(2*H1xy*cos(2*q1)+(H1xx-H1yy)*sin(2*q1))+2*cos(th) ... */
  /* 'CMatrix:704'   ^2*sin(phi)^2*(2*H1xy*cos(2*q1)+(H1xx-H1yy)*sin(2*q1))+ ... */
  /* 'CMatrix:705'   4*cos(phi)*cos(th)^2*sin(phi)*((-H2xx+H2yy)*cos(2*(q1+q2))+ ... */
  /* 'CMatrix:706'   2*H2xy*sin(2*(q1+q2)))+cos(th)^2*sin(phi)^2*(4*H2xy*cos(2*(q1+ ... */
  /* 'CMatrix:707'   q2))+2*(H2xx-H2yy)*sin(2*(q1+q2)))+cos(phi)^2*cos(th)^2*(( ... */
  /* 'CMatrix:708'   -4)*H2xy*cos(2*(q1+q2))+2*(-H2xx+H2yy)*sin(2*(q1+q2)))+4* ... */
  /* 'CMatrix:709'   ml2*((l1*sin(q1)+c2*sin(q1+q2))*(sin(phi)*sin(psi)+cos(phi)*cos( ... */
  /* 'CMatrix:710'   psi)*sin(th))+(l1*cos(q1)+c2*cos(q1+q2))*(-cos(phi)*sin(psi)+ ... */
  /* 'CMatrix:711'   cos(psi)*sin(phi)*sin(th)))*(-(L+l1*cos(q1)+c2*cos(q1+q2))*( ... */
  /* 'CMatrix:712'   sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))+(l1*sin(q1)+c2*sin(q1+ ... */
  /* 'CMatrix:713'   q2))*(-cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th)))+4*ml2*( ... */
  /* 'CMatrix:714'   cos(psi)*(L*sin(phi)+l1*sin(phi+q1)+c2*sin(phi+q1+q2))-(L* ... */
  /* 'CMatrix:715'   cos(phi)+l1*cos(phi+q1)+c2*cos(phi+q1+q2))*sin(psi)*sin(th))*((-1) ... */
  /* 'CMatrix:716'   *(l1*sin(q1)+c2*sin(q1+q2))*(cos(psi)*sin(phi)-cos(phi)*sin( ... */
  /* 'CMatrix:717'   psi)*sin(th))+(l1*cos(q1)+c2*cos(q1+q2))*(cos(phi)*cos(psi)+sin( ... */
  /* 'CMatrix:718'   phi)*sin(psi)*sin(th)))+4*c1*ml1*(-(L+c1*cos(q1))*(sin(phi) ... */
  /* 'CMatrix:719'   *sin(psi)+cos(phi)*cos(psi)*sin(th))+c1*sin(q1)*(-cos(phi)* ... */
  /* 'CMatrix:720'   sin(psi)+cos(psi)*sin(phi)*sin(th)))*(sin(phi)*(sin(psi)*sin(q1)+ ... */
  /* 'CMatrix:721'   cos(psi)*cos(q1)*sin(th))+cos(phi)*(-cos(q1)*sin(psi)+cos(psi) ... */
  /* 'CMatrix:722'   *sin(q1)*sin(th)))+4*ml1*(cos(psi)*(L*sin(phi)+c1*sin(phi+q1))+( ... */
  /* 'CMatrix:723'   -1)*(L*cos(phi)+c1*cos(phi+q1))*sin(psi)*sin(th))*(c1*sin(phi)*( ... */
  /* 'CMatrix:724'   -cos(psi)*sin(q1)+cos(q1)*sin(psi)*sin(th))+c1*cos(phi)*(cos( ... */
  /* 'CMatrix:725'   psi)*cos(q1)+sin(psi)*sin(q1)*sin(th)))+(-2)*sin(phi)*(H1zx*cos( ... */
  /* 'CMatrix:726'   q1)-H1yz*sin(q1))*sin(2*th)+(-2)*cos(phi)*(H1yz*cos(q1)+ ... */
  /* 'CMatrix:727'   H1zx*sin(q1))*sin(2*th)+(-2)*sin(phi)*(H2zx*cos(q1+q2)- ... */
  /* 'CMatrix:728'   H2yz*sin(q1+q2))*sin(2*th)+(-2)*cos(phi)*(H2yz*cos(q1+q2)+H2zx* ... */
  /* 'CMatrix:729'   sin(q1+q2))*sin(2*th))-dphi*cos(th)*(2*H1zx*cos(phi+q1+(-1) ... */
  /* 'CMatrix:730'   *th)+2*H1xy*cos(2*phi+2*q1-th)+2*H2zx*cos(phi+q1+q2- ... */
  /* 'CMatrix:731'   th)+2*H2xy*cos(2*phi+2*q1+2*q2-th)+(-2)*H1zx*cos(phi+q1+th) ... */
  /* 'CMatrix:732'   +2*H1xy*cos(2*phi+2*q1+th)+(-2)*H2zx*cos(phi+q1+q2+th)+2*H2xy* ... */
  /* 'CMatrix:733'   cos(2*phi+2*q1+2*q2+th)-Hby*sin(2*phi-th)+Hbz*sin(2* ... */
  /* 'CMatrix:734'   phi-th)-L^2*ml1*sin(2*phi-th)-L^2*ml2* ... */
  /* 'CMatrix:735'   sin(2*phi-th)+(-2)*H1yz*sin(phi+q1-th)+(-2)*c1*L*ml1* ... */
  /* 'CMatrix:736'   sin(2*phi+q1-th)+(-2)*L*l1*ml2*sin(2*phi+q1-th)+H1xx* ... */
  /* 'CMatrix:737'   sin(2*phi+2*q1-th)-H1yy*sin(2*phi+2*q1-th)- ... */
  /* 'CMatrix:738'   c1^2*ml1*sin(2*phi+2*q1-th)-l1^2*ml2*sin(2*phi+2* ... */
  /* 'CMatrix:739'   q1-th)+(-2)*H2yz*sin(phi+q1+q2-th)+(-2)*c2*L*ml2*sin( ... */
  /* 'CMatrix:740'   2*phi+q1+q2-th)+(-2)*c2*l1*ml2*sin(2*phi+2*q1+q2-th)+ ... */
  /* 'CMatrix:741'   H2xx*sin(2*phi+2*q1+2*q2-th)-H2yy*sin(2*phi+2*q1+2* ... */
  /* 'CMatrix:742'   q2-th)-c2^2*ml2*sin(2*phi+2*q1+2*q2-th)- ... */
  /* 'CMatrix:743'   Hby*sin(2*phi+th)+Hbz*sin(2*phi+th)-L^2*ml1*sin(2*phi+th)+ ... */
  /* 'CMatrix:744'   -L^2*ml2*sin(2*phi+th)+2*H1yz*sin(phi+q1+th)+(-2)*c1*L* ... */
  /* 'CMatrix:745'   ml1*sin(2*phi+q1+th)+(-2)*L*l1*ml2*sin(2*phi+q1+th)+H1xx*sin(2* ... */
  /* 'CMatrix:746'   phi+2*q1+th)-H1yy*sin(2*phi+2*q1+th)-c1^2*ml1*sin(2* ... */
  /* 'CMatrix:747'   phi+2*q1+th)-l1^2*ml2*sin(2*phi+2*q1+th)+2*H2yz*sin(phi+ ... */
  /* 'CMatrix:748'   q1+q2+th)+(-2)*c2*L*ml2*sin(2*phi+q1+q2+th)+(-2)*c2*l1*ml2*sin( ... */
  /* 'CMatrix:749'   2*phi+2*q1+q2+th)+H2xx*sin(2*phi+2*q1+2*q2+th)-H2yy*sin(2* ... */
  /* 'CMatrix:750'   phi+2*q1+2*q2+th)-c2^2*ml2*sin(2*phi+2*q1+2*q2+th))); */
  D24 = std::cos(rtu_InBus1_Positions[3]);
  D25 = std::cos(rtu_InBus1_Positions[6]);
  D14_tmp_tmp = std::sin(rtu_InBus1_Positions[6]);
  D27 = std::sin(rtu_InBus1_Positions[3]);
  D28 = std::cos(rtu_InBus1_Positions[6]);
  D34 = std::sin(rtu_InBus1_Positions[6]);
  D35 = std::cos(rtu_InBus1_Positions[3]);
  D37 = std::sin(rtu_InBus1_Positions[3]);
  D38 = std::cos(rtu_InBus1_Positions[3]);
  D45 = std::sin(rtu_InBus1_Positions[3]);
  D46_tmp_e = std::cos(rtu_InBus1_Positions[4]);
  D47 = std::cos(rtu_InBus1_Positions[4]);
  D48 = std::sin(rtu_InBus1_Positions[3]);
  D56 = std::cos(rtu_InBus1_Positions[3]);
  D57 = std::cos(rtu_InBus1_Positions[4]);
  D45_tmp = std::cos(rtu_InBus1_Positions[4]);
  D45_tmp_0 = std::cos(rtu_InBus1_Positions[3]);
  c_a = std::cos(rtu_InBus1_Positions[4]);
  d_a = std::cos(rtu_InBus1_Positions[4]);
  e_a = std::sin(rtu_InBus1_Positions[3]);
  f_a = std::cos(rtu_InBus1_Positions[4]);
  g_a = std::cos(rtu_InBus1_Positions[4]);
  h_a = std::sin(rtu_InBus1_Positions[3]);
  i_a = std::cos(rtu_InBus1_Positions[3]);
  j_a = std::cos(rtu_InBus1_Positions[4]);

  /* 'CMatrix:751' C67=(1/8)*((-4)*dpsi*H1xy*cos(2*(phi+q1))+(-4)*dpsi*H2xy*cos(2*( ... */
  /* 'CMatrix:752'   phi+q1+q2))+(-2)*dpsi*H1zx*cos(phi+q1+(-2)*th)+(-2)*dpsi*H2zx* ... */
  /* 'CMatrix:753'   cos(phi+q1+q2+(-2)*th)+4*c1*dphi*L*ml1*cos(q1-th)+(-2)*c1* ... */
  /* 'CMatrix:754'   dth*L*ml1*cos(q1-th)+4*dphi*L*l1*ml2*cos(q1-th)+(-2) ... */
  /* 'CMatrix:755'   *dth*L*l1*ml2*cos(q1-th)+4*dphi*H1yz*cos(phi+q1-th)+ ... */
  /* 'CMatrix:756'   (-2)*dpsi*H1xy*cos(2*(phi+q1-th))+2*c1*dth*L*ml1*cos(2* ... */
  /* 'CMatrix:757'   phi+q1-th)+2*dth*L*l1*ml2*cos(2*phi+q1-th)+(-2)*dth* ... */
  /* 'CMatrix:758'   H1xx*cos(2*phi+2*q1-th)+2*dth*H1yy*cos(2*phi+2*q1- ... */
  /* 'CMatrix:759'   th)+2*c1^2*dth*ml1*cos(2*phi+2*q1-th)+2*dth*l1^2*ml2* ... */
  /* 'CMatrix:760'   cos(2*phi+2*q1-th)+(-4)*c2*dth*l1*ml2*cos(q2-th)+4* ... */
  /* 'CMatrix:761'   c2*dphi*L*ml2*cos(q1+q2-th)+(-2)*c2*dth*L*ml2*cos(q1+q2+( ... */
  /* 'CMatrix:762'   -1)*th)+4*dphi*H2yz*cos(phi+q1+q2-th)+(-2)*dpsi*H2xy*cos( ... */
  /* 'CMatrix:763'   2*(phi+q1+q2-th))+2*c2*dth*L*ml2*cos(2*phi+q1+q2-th)+ ... */
  /* 'CMatrix:764'   4*c2*dth*l1*ml2*cos(2*phi+2*q1+q2-th)+(-2)*dth*H2xx*cos( ... */
  /* 'CMatrix:765'   2*phi+2*q1+2*q2-th)+2*dth*H2yy*cos(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:766'   th)+2*c2^2*dth*ml2*cos(2*phi+2*q1+2*q2-th)+(-4)*dth* ... */
  /* 'CMatrix:767'   H1zz*cos(th)+(-4)*dth*H2zz*cos(th)+(-4)*c1^2*dth*ml1*cos(th)+( ... */
  /* 'CMatrix:768'   -4)*c2^2*dth*ml2*cos(th)+(-4)*dth*l1^2*ml2*cos(th)+(-4)*c1* ... */
  /* 'CMatrix:769'   dphi*L*ml1*cos(q1+th)+(-2)*c1*dth*L*ml1*cos(q1+th)+(-4)*dphi* ... */
  /* 'CMatrix:770'   L*l1*ml2*cos(q1+th)+(-2)*dth*L*l1*ml2*cos(q1+th)+4*dphi*H1yz* ... */
  /* 'CMatrix:771'   cos(phi+q1+th)+(-2)*dpsi*H1xy*cos(2*(phi+q1+th))+2*c1*dth*L* ... */
  /* 'CMatrix:772'   ml1*cos(2*phi+q1+th)+2*dth*L*l1*ml2*cos(2*phi+q1+th)+(-2)*dth* ... */
  /* 'CMatrix:773'   H1xx*cos(2*phi+2*q1+th)+2*dth*H1yy*cos(2*phi+2*q1+th)+2*c1^2* ... */
  /* 'CMatrix:774'   dth*ml1*cos(2*phi+2*q1+th)+2*dth*l1^2*ml2*cos(2*phi+2*q1+th)+ ... */
  /* 'CMatrix:775'   (-4)*c2*dth*l1*ml2*cos(q2+th)+(-4)*c2*dphi*L*ml2*cos(q1+q2+th) ... */
  /* 'CMatrix:776'   +(-2)*c2*dth*L*ml2*cos(q1+q2+th)+4*dphi*H2yz*cos(phi+q1+q2+th)+( ... */
  /* 'CMatrix:777'   -2)*dpsi*H2xy*cos(2*(phi+q1+q2+th))+2*c2*dth*L*ml2*cos(2*phi+ ... */
  /* 'CMatrix:778'   q1+q2+th)+4*c2*dth*l1*ml2*cos(2*phi+2*q1+q2+th)+(-2)*dth*H2xx* ... */
  /* 'CMatrix:779'   cos(2*phi+2*q1+2*q2+th)+2*dth*H2yy*cos(2*phi+2*q1+2*q2+th)+2* ... */
  /* 'CMatrix:780'   c2^2*dth*ml2*cos(2*phi+2*q1+2*q2+th)+2*dpsi*H1zx*cos(phi+q1+ ... */
  /* 'CMatrix:781'   2*th)+2*dpsi*H2zx*cos(phi+q1+q2+2*th)+(-6)*c1*dpsi*L*ml1*sin( ... */
  /* 'CMatrix:782'   q1)+(-6)*dpsi*L*l1*ml2*sin(q1)+(-2)*dpsi*H1xx*sin(2*(phi+q1))+ ... */
  /* 'CMatrix:783'   2*dpsi*H1yy*sin(2*(phi+q1))+2*c1^2*dpsi*ml1*sin(2*(phi+q1))+ ... */
  /* 'CMatrix:784'   2*dpsi*l1^2*ml2*sin(2*(phi+q1))+2*c1*dpsi*L*ml1*sin(2*phi+ ... */
  /* 'CMatrix:785'   q1)+2*dpsi*L*l1*ml2*sin(2*phi+q1)+(-6)*c2*dpsi*L*ml2*sin(q1+ ... */
  /* 'CMatrix:786'   q2)+(-2)*dpsi*H2xx*sin(2*(phi+q1+q2))+2*dpsi*H2yy*sin(2*(phi+q1+ ... */
  /* 'CMatrix:787'   q2))+2*c2^2*dpsi*ml2*sin(2*(phi+q1+q2))+2*c2*dpsi*L*ml2*sin( ... */
  /* 'CMatrix:788'   2*phi+q1+q2)+4*c2*dpsi*l1*ml2*sin(2*(phi+q1)+q2)+2*c2*dpsi* ... */
  /* 'CMatrix:789'   l1*ml2*sin(q2+2*(phi+q1-th))+c1*dpsi*L*ml1*sin(q1+(-2)*th) ... */
  /* 'CMatrix:790'   +dpsi*L*l1*ml2*sin(q1+(-2)*th)+2*dpsi*H1yz*sin(phi+q1+(-2)*th)+ ... */
  /* 'CMatrix:791'   c1*dpsi*L*ml1*sin(2*phi+q1+(-2)*th)+dpsi*L*l1*ml2*sin(2*phi+ ... */
  /* 'CMatrix:792'   q1+(-2)*th)+c2*dpsi*L*ml2*sin(q1+q2+(-2)*th)+2*dpsi*H2yz*sin( ... */
  /* 'CMatrix:793'   phi+q1+q2+(-2)*th)+c2*dpsi*L*ml2*sin(2*phi+q1+q2+(-2)*th)+4* ... */
  /* 'CMatrix:794'   dphi*H1zx*sin(phi+q1-th)-dpsi*H1xx*sin(2*(phi+q1- ... */
  /* 'CMatrix:795'   th))+dpsi*H1yy*sin(2*(phi+q1-th))+c1^2*dpsi*ml1*sin(2*( ... */
  /* 'CMatrix:796'   phi+q1-th))+dpsi*l1^2*ml2*sin(2*(phi+q1-th))+4*dth* ... */
  /* 'CMatrix:797'   H1xy*sin(2*phi+2*q1-th)+4*dphi*H2zx*sin(phi+q1+q2-th)+ ... */
  /* 'CMatrix:798'   -dpsi*H2xx*sin(2*(phi+q1+q2-th))+dpsi*H2yy*sin(2*(phi+ ... */
  /* 'CMatrix:799'   q1+q2-th))+c2^2*dpsi*ml2*sin(2*(phi+q1+q2-th))+4*dth* ... */
  /* 'CMatrix:800'   H2xy*sin(2*phi+2*q1+2*q2-th)+4*dphi*H1zx*sin(phi+q1+th)+( ... */
  /* 'CMatrix:801'   -1)*dpsi*H1xx*sin(2*(phi+q1+th))+dpsi*H1yy*sin(2*(phi+q1+th))+ ... */
  /* 'CMatrix:802'   c1^2*dpsi*ml1*sin(2*(phi+q1+th))+dpsi*l1^2*ml2*sin(2*(phi+q1+ ... */
  /* 'CMatrix:803'   th))+4*dth*H1xy*sin(2*phi+2*q1+th)+4*dphi*H2zx*sin(phi+q1+q2+th) ... */
  /* 'CMatrix:804'   +4*dq2*(c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2-th)+ ... */
  /* 'CMatrix:805'   H2yz*cos(phi+q1+q2-th)-c2*l1*ml2*cos(q2+th)-c2* ... */
  /* 'CMatrix:806'   L*ml2*cos(q1+q2+th)+H2yz*cos(phi+q1+q2+th)+H2zx*sin(phi+q1+q2- ... */
  /* 'CMatrix:807'   th)+H2zx*sin(phi+q1+q2+th))+4*dq1*(L*(c1*ml1+l1*ml2)*cos(q1+(-1) ... */
  /* 'CMatrix:808'   *th)+H1yz*cos(phi+q1-th)+c2*L*ml2*cos(q1+q2-th)+H2yz* ... */
  /* 'CMatrix:809'   cos(phi+q1+q2-th)-c1*L*ml1*cos(q1+th)-L*l1*ml2* ... */
  /* 'CMatrix:810'   cos(q1+th)+H1yz*cos(phi+q1+th)-c2*L*ml2*cos(q1+q2+th)+H2yz* ... */
  /* 'CMatrix:811'   cos(phi+q1+q2+th)+H1zx*sin(phi+q1-th)+H2zx*sin(phi+q1+q2- ... */
  /* 'CMatrix:812'   th)+H1zx*sin(phi+q1+th)+H2zx*sin(phi+q1+q2+th))-dpsi*H2xx*sin( ... */
  /* 'CMatrix:813'   2*(phi+q1+q2+th))+dpsi*H2yy*sin(2*(phi+q1+q2+th))+c2^2*dpsi*ml2* ... */
  /* 'CMatrix:814'   sin(2*(phi+q1+q2+th))+4*dth*H2xy*sin(2*phi+2*q1+2*q2+th)+c1* ... */
  /* 'CMatrix:815'   dpsi*L*ml1*sin(q1+2*th)+dpsi*L*l1*ml2*sin(q1+2*th)+(-2)*dpsi* ... */
  /* 'CMatrix:816'   H1yz*sin(phi+q1+2*th)+c2*dpsi*L*ml2*sin(q1+q2+2*th)+(-2)*dpsi* ... */
  /* 'CMatrix:817'   H2yz*sin(phi+q1+q2+2*th)+c1*dpsi*L*ml1*sin(q1+2*(phi+th))+dpsi* ... */
  /* 'CMatrix:818'   L*l1*ml2*sin(q1+2*(phi+th))+c2*dpsi*L*ml2*sin(q1+q2+2*(phi+th)) ... */
  /* 'CMatrix:819'   +2*c2*dpsi*l1*ml2*sin(q2+2*(phi+q1+th))); */
  /* 'CMatrix:820' C68=(1/8)*((-4)*dpsi*H2xy*cos(2*(phi+q1+q2))+(-2)*dpsi*H2zx*cos(phi+ ... */
  /* 'CMatrix:821'   q1+q2+(-2)*th)+4*c2*dphi*l1*ml2*cos(q2-th)+(-2)*c2*dth* ... */
  /* 'CMatrix:822'   l1*ml2*cos(q2-th)+4*c2*dphi*L*ml2*cos(q1+q2-th)+(-2) ... */
  /* 'CMatrix:823'   *c2*dth*L*ml2*cos(q1+q2-th)+4*dphi*H2yz*cos(phi+q1+q2+(-1) ... */
  /* 'CMatrix:824'   *th)+(-2)*dpsi*H2xy*cos(2*(phi+q1+q2-th))+2*c2*dth*L* ... */
  /* 'CMatrix:825'   ml2*cos(2*phi+q1+q2-th)+2*c2*dth*l1*ml2*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:826'   q2-th)+(-2)*dth*H2xx*cos(2*phi+2*q1+2*q2-th)+2*dth* ... */
  /* 'CMatrix:827'   H2yy*cos(2*phi+2*q1+2*q2-th)+2*c2^2*dth*ml2*cos(2*phi+ ... */
  /* 'CMatrix:828'   2*q1+2*q2-th)+(-4)*dth*H2zz*cos(th)+(-4)*c2^2*dth*ml2* ... */
  /* 'CMatrix:829'   cos(th)+(-4)*c2*dphi*l1*ml2*cos(q2+th)+(-2)*c2*dth*l1*ml2*cos( ... */
  /* 'CMatrix:830'   q2+th)+(-4)*c2*dphi*L*ml2*cos(q1+q2+th)+(-2)*c2*dth*L*ml2*cos( ... */
  /* 'CMatrix:831'   q1+q2+th)+4*dphi*H2yz*cos(phi+q1+q2+th)+(-2)*dpsi*H2xy*cos(2*( ... */
  /* 'CMatrix:832'   phi+q1+q2+th))+2*c2*dth*L*ml2*cos(2*phi+q1+q2+th)+2*c2*dth*l1* ... */
  /* 'CMatrix:833'   ml2*cos(2*phi+2*q1+q2+th)+(-2)*dth*H2xx*cos(2*phi+2*q1+2*q2+th) ... */
  /* 'CMatrix:834'   +2*dth*H2yy*cos(2*phi+2*q1+2*q2+th)+2*c2^2*dth*ml2*cos(2* ... */
  /* 'CMatrix:835'   phi+2*q1+2*q2+th)+2*dpsi*H2zx*cos(phi+q1+q2+2*th)+(-6)*c2*dpsi* ... */
  /* 'CMatrix:836'   l1*ml2*sin(q2)+(-6)*c2*dpsi*L*ml2*sin(q1+q2)+(-2)*dpsi*H2xx* ... */
  /* 'CMatrix:837'   sin(2*(phi+q1+q2))+2*dpsi*H2yy*sin(2*(phi+q1+q2))+2*c2^2*dpsi* ... */
  /* 'CMatrix:838'   ml2*sin(2*(phi+q1+q2))+2*c2*dpsi*L*ml2*sin(2*phi+q1+q2)+2*c2* ... */
  /* 'CMatrix:839'   dpsi*l1*ml2*sin(2*(phi+q1)+q2)+c2*dpsi*l1*ml2*sin(q2+2*(phi+q1+ ... */
  /* 'CMatrix:840'   -th))+c2*dpsi*l1*ml2*sin(q2+(-2)*th)+c2*dpsi*L*ml2*sin(q1+ ... */
  /* 'CMatrix:841'   q2+(-2)*th)+2*dpsi*H2yz*sin(phi+q1+q2+(-2)*th)+c2*dpsi*L*ml2* ... */
  /* 'CMatrix:842'   sin(2*phi+q1+q2+(-2)*th)+4*dphi*H2zx*sin(phi+q1+q2-th)- ... */
  /* 'CMatrix:843'   dpsi*H2xx*sin(2*(phi+q1+q2-th))+dpsi*H2yy*sin(2*(phi+q1+q2+( ... */
  /* 'CMatrix:844'   -1)*th))+c2^2*dpsi*ml2*sin(2*(phi+q1+q2-th))+4*dth*H2xy* ... */
  /* 'CMatrix:845'   sin(2*phi+2*q1+2*q2-th)+4*dphi*H2zx*sin(phi+q1+q2+th)+4* ... */
  /* 'CMatrix:846'   dq1*(c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2-th)+ ... */
  /* 'CMatrix:847'   H2yz*cos(phi+q1+q2-th)-c2*l1*ml2*cos(q2+th)-c2* ... */
  /* 'CMatrix:848'   L*ml2*cos(q1+q2+th)+H2yz*cos(phi+q1+q2+th)+H2zx*sin(phi+q1+q2- ... */
  /* 'CMatrix:849'   th)+H2zx*sin(phi+q1+q2+th))+4*dq2*(c2*l1*ml2*cos(q2-th)+c2* ... */
  /* 'CMatrix:850'   L*ml2*cos(q1+q2-th)+H2yz*cos(phi+q1+q2-th)-c2*l1* ... */
  /* 'CMatrix:851'   ml2*cos(q2+th)-c2*L*ml2*cos(q1+q2+th)+H2yz*cos(phi+q1+q2+th)+ ... */
  /* 'CMatrix:852'   H2zx*sin(phi+q1+q2-th)+H2zx*sin(phi+q1+q2+th))-dpsi* ... */
  /* 'CMatrix:853'   H2xx*sin(2*(phi+q1+q2+th))+dpsi*H2yy*sin(2*(phi+q1+q2+th))+c2^2* ... */
  /* 'CMatrix:854'   dpsi*ml2*sin(2*(phi+q1+q2+th))+4*dth*H2xy*sin(2*phi+2*q1+2*q2+ ... */
  /* 'CMatrix:855'   th)+c2*dpsi*l1*ml2*sin(q2+2*th)+c2*dpsi*L*ml2*sin(q1+q2+2*th)+ ... */
  /* 'CMatrix:856'   (-2)*dpsi*H2yz*sin(phi+q1+q2+2*th)+c2*dpsi*L*ml2*sin(q1+q2+2*( ... */
  /* 'CMatrix:857'   phi+th))+c2*dpsi*l1*ml2*sin(q2+2*(phi+q1+th))); */
  /* 'CMatrix:42' [C74, C75, C76, C77, C78] = get_C7(); */
  /* 'CMatrix:861' C74=-c2*dq2*l1*ml2*sin(q2)+L*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2* ... */
  /* 'CMatrix:862'   sin(q1+q2))*(dphi-dpsi*sin(th)); */
  /* 'CMatrix:863' C75=(1/4)*(2*dth*((-2)*H1xy*cos(2*(phi+q1))+(-2)*H2xy*cos(2*(phi+ ... */
  /* 'CMatrix:864'   q1+q2))+c1*L*ml1*sin(q1)+L*l1*ml2*sin(q1)-H1xx*sin(2*(phi+ ... */
  /* 'CMatrix:865'   q1))+H1yy*sin(2*(phi+q1))+c1^2*ml1*sin(2*(phi+q1))+l1^2*ml2* ... */
  /* 'CMatrix:866'   sin(2*(phi+q1))+c1*L*ml1*sin(2*phi+q1)+L*l1*ml2*sin(2*phi+q1)+ ... */
  /* 'CMatrix:867'   c2*L*ml2*sin(q1+q2)-H2xx*sin(2*(phi+q1+q2))+H2yy*sin(2*( ... */
  /* 'CMatrix:868'   phi+q1+q2))+c2^2*ml2*sin(2*(phi+q1+q2))+c2*L*ml2*sin(2*phi+q1+ ... */
  /* 'CMatrix:869'   q2)+2*c2*l1*ml2*sin(2*(phi+q1)+q2))-dpsi*(L*(c1*ml1+l1* ... */
  /* 'CMatrix:870'   ml2)*cos(q1-th)+2*H1yz*cos(phi+q1-th)+c1*L*ml1*cos(2* ... */
  /* 'CMatrix:871'   phi+q1-th)+L*l1*ml2*cos(2*phi+q1-th)-H1xx*cos(2* ... */
  /* 'CMatrix:872'   phi+2*q1-th)+H1yy*cos(2*phi+2*q1-th)+c1^2*ml1*cos(2* ... */
  /* 'CMatrix:873'   phi+2*q1-th)+l1^2*ml2*cos(2*phi+2*q1-th)+2*c2*l1* ... */
  /* 'CMatrix:874'   ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2-th)+2*H2yz*cos(phi+ ... */
  /* 'CMatrix:875'   q1+q2-th)+c2*L*ml2*cos(2*phi+q1+q2-th)+2*c2*l1*ml2* ... */
  /* 'CMatrix:876'   cos(2*phi+2*q1+q2-th)-H2xx*cos(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:877'   th)+H2yy*cos(2*phi+2*q1+2*q2-th)+c2^2*ml2*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:878'   2*q2-th)+2*H1zz*cos(th)+2*H2zz*cos(th)+2*c1^2*ml1*cos(th) ... */
  /* 'CMatrix:879'   +2*c2^2*ml2*cos(th)+2*l1^2*ml2*cos(th)+c1*L*ml1*cos(q1+th)+ ... */
  /* 'CMatrix:880'   L*l1*ml2*cos(q1+th)+(-2)*H1yz*cos(phi+q1+th)+c1*L*ml1*cos(2* ... */
  /* 'CMatrix:881'   phi+q1+th)+L*l1*ml2*cos(2*phi+q1+th)-H1xx*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:882'   th)+H1yy*cos(2*phi+2*q1+th)+c1^2*ml1*cos(2*phi+2*q1+th)+l1^2* ... */
  /* 'CMatrix:883'   ml2*cos(2*phi+2*q1+th)+2*c2*l1*ml2*cos(q2+th)+c2*L*ml2*cos(q1+ ... */
  /* 'CMatrix:884'   q2+th)+(-2)*H2yz*cos(phi+q1+q2+th)+c2*L*ml2*cos(2*phi+q1+q2+th)+ ... */
  /* 'CMatrix:885'   2*c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:886'   q2+th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:887'   q2+th)+2*H1zx*sin(phi+q1-th)+2*H1xy*sin(2*phi+2*q1-th) ... */
  /* 'CMatrix:888'   +2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:889'   th)+(-2)*H1zx*sin(phi+q1+th)+2*H1xy*sin(2*phi+2*q1+th)+(-2)* ... */
  /* 'CMatrix:890'   H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+2*q2+th))); */
  /* 'CMatrix:891' C76=(1/8)*(4*dpsi*H1xy*cos(2*(phi+q1))+4*dpsi*H2xy*cos(2*(phi+q1+ ... */
  /* 'CMatrix:892'   q2))+2*dpsi*H1zx*cos(phi+q1+(-2)*th)+2*dpsi*H2zx*cos(phi+q1+q2+( ... */
  /* 'CMatrix:893'   -2)*th)+(-4)*c1*dphi*L*ml1*cos(q1-th)+(-4)*dphi*L*l1* ... */
  /* 'CMatrix:894'   ml2*cos(q1-th)+2*dpsi*H1xy*cos(2*(phi+q1-th))+(-4)* ... */
  /* 'CMatrix:895'   c2*dphi*L*ml2*cos(q1+q2-th)+2*dpsi*H2xy*cos(2*(phi+q1+q2+( ... */
  /* 'CMatrix:896'   -1)*th))+4*c1*dphi*L*ml1*cos(q1+th)+4*dphi*L*l1*ml2*cos(q1+ ... */
  /* 'CMatrix:897'   th)+2*dpsi*H1xy*cos(2*(phi+q1+th))+4*c2*dphi*L*ml2*cos(q1+q2+ ... */
  /* 'CMatrix:898'   th)+2*dpsi*H2xy*cos(2*(phi+q1+q2+th))+(-2)*dpsi*H1zx*cos(phi+q1+ ... */
  /* 'CMatrix:899'   2*th)+(-2)*dpsi*H2zx*cos(phi+q1+q2+2*th)+6*c1*dpsi*L*ml1*sin( ... */
  /* 'CMatrix:900'   q1)+6*dpsi*L*l1*ml2*sin(q1)+2*dpsi*H1xx*sin(2*(phi+q1))+(-2)* ... */
  /* 'CMatrix:901'   dpsi*H1yy*sin(2*(phi+q1))+(-2)*c1^2*dpsi*ml1*sin(2*(phi+q1))+( ... */
  /* 'CMatrix:902'   -2)*dpsi*l1^2*ml2*sin(2*(phi+q1))+(-2)*c1*dpsi*L*ml1*sin(2* ... */
  /* 'CMatrix:903'   phi+q1)+(-2)*dpsi*L*l1*ml2*sin(2*phi+q1)+6*c2*dpsi*L*ml2*sin( ... */
  /* 'CMatrix:904'   q1+q2)+2*dpsi*H2xx*sin(2*(phi+q1+q2))+(-2)*dpsi*H2yy*sin(2*(phi+ ... */
  /* 'CMatrix:905'   q1+q2))+(-2)*c2^2*dpsi*ml2*sin(2*(phi+q1+q2))+(-2)*c2*dpsi*L* ... */
  /* 'CMatrix:906'   ml2*sin(2*phi+q1+q2)+(-4)*c2*dpsi*l1*ml2*sin(2*(phi+q1)+q2)+(-2) ... */
  /* 'CMatrix:907'   *c2*dpsi*l1*ml2*sin(q2+2*(phi+q1-th))-c1*dpsi*L* ... */
  /* 'CMatrix:908'   ml1*sin(q1+(-2)*th)-dpsi*L*l1*ml2*sin(q1+(-2)*th)+(-2)* ... */
  /* 'CMatrix:909'   dpsi*H1yz*sin(phi+q1+(-2)*th)-c1*dpsi*L*ml1*sin(2*phi+q1+( ... */
  /* 'CMatrix:910'   -2)*th)-dpsi*L*l1*ml2*sin(2*phi+q1+(-2)*th)-c2* ... */
  /* 'CMatrix:911'   dpsi*L*ml2*sin(q1+q2+(-2)*th)+(-2)*dpsi*H2yz*sin(phi+q1+q2+(-2)* ... */
  /* 'CMatrix:912'   th)-c2*dpsi*L*ml2*sin(2*phi+q1+q2+(-2)*th)+dpsi*H1xx*sin( ... */
  /* 'CMatrix:913'   2*(phi+q1-th))-dpsi*H1yy*sin(2*(phi+q1-th))- ... */
  /* 'CMatrix:914'   c1^2*dpsi*ml1*sin(2*(phi+q1-th))-dpsi*l1^2*ml2*sin( ... */
  /* 'CMatrix:915'   2*(phi+q1-th))+dpsi*H2xx*sin(2*(phi+q1+q2-th))- ... */
  /* 'CMatrix:916'   dpsi*H2yy*sin(2*(phi+q1+q2-th))-c2^2*dpsi*ml2*sin(2* ... */
  /* 'CMatrix:917'   (phi+q1+q2-th))+8*c2*dq2*l1*ml2*sin(q2)*sin(th)+dpsi*H1xx* ... */
  /* 'CMatrix:918'   sin(2*(phi+q1+th))-dpsi*H1yy*sin(2*(phi+q1+th))-c1^2* ... */
  /* 'CMatrix:919'   dpsi*ml1*sin(2*(phi+q1+th))-dpsi*l1^2*ml2*sin(2*(phi+q1+ ... */
  /* 'CMatrix:920'   th))+dpsi*H2xx*sin(2*(phi+q1+q2+th))-dpsi*H2yy*sin(2*(phi+ ... */
  /* 'CMatrix:921'   q1+q2+th))-c2^2*dpsi*ml2*sin(2*(phi+q1+q2+th))+(-2)*dth*( ... */
  /* 'CMatrix:922'   L*(c1*ml1+l1*ml2)*cos(q1-th)+2*H1yz*cos(phi+q1-th)+ ... */
  /* 'CMatrix:923'   c1*L*ml1*cos(2*phi+q1-th)+L*l1*ml2*cos(2*phi+q1-th)+ ... */
  /* 'CMatrix:924'   -H1xx*cos(2*phi+2*q1-th)+H1yy*cos(2*phi+2*q1-th)+ ... */
  /* 'CMatrix:925'   c1^2*ml1*cos(2*phi+2*q1-th)+l1^2*ml2*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:926'   *th)+2*c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2-th)+ ... */
  /* 'CMatrix:927'   2*H2yz*cos(phi+q1+q2-th)+c2*L*ml2*cos(2*phi+q1+q2-th)+ ... */
  /* 'CMatrix:928'   2*c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx*cos(2*phi+2* ... */
  /* 'CMatrix:929'   q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+c2^2*ml2* ... */
  /* 'CMatrix:930'   cos(2*phi+2*q1+2*q2-th)+2*H1zz*cos(th)+2*H2zz*cos(th)+2* ... */
  /* 'CMatrix:931'   c1^2*ml1*cos(th)+2*c2^2*ml2*cos(th)+2*l1^2*ml2*cos(th)+c1* ... */
  /* 'CMatrix:932'   L*ml1*cos(q1+th)+L*l1*ml2*cos(q1+th)+(-2)*H1yz*cos(phi+q1+th)+ ... */
  /* 'CMatrix:933'   c1*L*ml1*cos(2*phi+q1+th)+L*l1*ml2*cos(2*phi+q1+th)-H1xx* ... */
  /* 'CMatrix:934'   cos(2*phi+2*q1+th)+H1yy*cos(2*phi+2*q1+th)+c1^2*ml1*cos(2*phi+ ... */
  /* 'CMatrix:935'   2*q1+th)+l1^2*ml2*cos(2*phi+2*q1+th)+2*c2*l1*ml2*cos(q2+th)+ ... */
  /* 'CMatrix:936'   c2*L*ml2*cos(q1+q2+th)+(-2)*H2yz*cos(phi+q1+q2+th)+c2*L*ml2*cos( ... */
  /* 'CMatrix:937'   2*phi+q1+q2+th)+2*c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx* ... */
  /* 'CMatrix:938'   cos(2*phi+2*q1+2*q2+th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2* ... */
  /* 'CMatrix:939'   cos(2*phi+2*q1+2*q2+th)+2*H1zx*sin(phi+q1-th)+2*H1xy*sin( ... */
  /* 'CMatrix:940'   2*phi+2*q1-th)+2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2* ... */
  /* 'CMatrix:941'   phi+2*q1+2*q2-th)+(-2)*H1zx*sin(phi+q1+th)+2*H1xy*sin(2* ... */
  /* 'CMatrix:942'   phi+2*q1+th)+(-2)*H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+ ... */
  /* 'CMatrix:943'   2*q2+th))-c1*dpsi*L*ml1*sin(q1+2*th)-dpsi*L*l1* ... */
  /* 'CMatrix:944'   ml2*sin(q1+2*th)+2*dpsi*H1yz*sin(phi+q1+2*th)-c2*dpsi*L* ... */
  /* 'CMatrix:945'   ml2*sin(q1+q2+2*th)+2*dpsi*H2yz*sin(phi+q1+q2+2*th)-c1* ... */
  /* 'CMatrix:946'   dpsi*L*ml1*sin(q1+2*(phi+th))-dpsi*L*l1*ml2*sin(q1+2*( ... */
  /* 'CMatrix:947'   phi+th))-c2*dpsi*L*ml2*sin(q1+q2+2*(phi+th))+(-2)*c2*dpsi* ... */
  /* 'CMatrix:948'   l1*ml2*sin(q2+2*(phi+q1+th))); */
  /* 'CMatrix:949' C77=-c2*dq2*l1*ml2*sin(q2); */
  /* 'CMatrix:950' C78=-c2*l1*ml2*sin(q2)*(dphi+dq1+dq2-dpsi*sin(th)); */
  /* 'CMatrix:43' [C84, C85, C86, C87, C88] = get_C8(); */
  /* 'CMatrix:954' C84=c2*ml2*(dq1*l1*sin(q2)+(l1*sin(q2)+L*sin(q1+q2))*(dphi- ... */
  /* 'CMatrix:955'   dpsi*sin(th))); */
  /* 'CMatrix:956' C85=-dth*H2xy*cos(2*(phi+q1+q2))+dth*(c2*L*ml2*cos(phi)+c2*l1* ... */
  /* 'CMatrix:957'   ml2*cos(phi+q1)+(-H2xx+H2yy+c2^2*ml2)*cos(phi+q1+q2))*sin(phi+ ... */
  /* 'CMatrix:958'   q1+q2)+(-1/4)*dpsi*(c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+ ... */
  /* 'CMatrix:959'   q2-th)+2*H2yz*cos(phi+q1+q2-th)+c2*L*ml2*cos(2*phi+q1+ ... */
  /* 'CMatrix:960'   q2-th)+c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx*cos( ... */
  /* 'CMatrix:961'   2*phi+2*q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:962'   c2^2*ml2*cos(2*phi+2*q1+2*q2-th)+2*H2zz*cos(th)+2*c2^2* ... */
  /* 'CMatrix:963'   ml2*cos(th)+c2*l1*ml2*cos(q2+th)+c2*L*ml2*cos(q1+q2+th)+(-2)* ... */
  /* 'CMatrix:964'   H2yz*cos(phi+q1+q2+th)+c2*L*ml2*cos(2*phi+q1+q2+th)+c2*l1*ml2* ... */
  /* 'CMatrix:965'   cos(2*phi+2*q1+q2+th)-H2xx*cos(2*phi+2*q1+2*q2+th)+H2yy* ... */
  /* 'CMatrix:966'   cos(2*phi+2*q1+2*q2+th)+c2^2*ml2*cos(2*phi+2*q1+2*q2+th)+2* ... */
  /* 'CMatrix:967'   H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:968'   (-2)*H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+2*q2+th)); */
  /* 'CMatrix:969' C86=(1/8)*(4*dpsi*H2xy*cos(2*(phi+q1+q2))+2*dpsi*H2zx*cos(phi+q1+q2+ ... */
  /* 'CMatrix:970'   (-2)*th)+(-4)*c2*dphi*l1*ml2*cos(q2-th)+(-4)*c2*dphi*L* ... */
  /* 'CMatrix:971'   ml2*cos(q1+q2-th)+2*dpsi*H2xy*cos(2*(phi+q1+q2-th))+4* ... */
  /* 'CMatrix:972'   c2*dphi*l1*ml2*cos(q2+th)+4*c2*dphi*L*ml2*cos(q1+q2+th)+2* ... */
  /* 'CMatrix:973'   dpsi*H2xy*cos(2*(phi+q1+q2+th))+(-2)*dpsi*H2zx*cos(phi+q1+q2+2* ... */
  /* 'CMatrix:974'   th)+6*c2*dpsi*l1*ml2*sin(q2)+6*c2*dpsi*L*ml2*sin(q1+q2)+2* ... */
  /* 'CMatrix:975'   dpsi*H2xx*sin(2*(phi+q1+q2))+(-2)*dpsi*H2yy*sin(2*(phi+q1+q2))+( ... */
  /* 'CMatrix:976'   -2)*c2^2*dpsi*ml2*sin(2*(phi+q1+q2))+(-2)*c2*dpsi*L*ml2*sin( ... */
  /* 'CMatrix:977'   2*phi+q1+q2)+(-2)*c2*dpsi*l1*ml2*sin(2*(phi+q1)+q2)-c2* ... */
  /* 'CMatrix:978'   dpsi*l1*ml2*sin(q2+2*(phi+q1-th))-c2*dpsi*l1*ml2* ... */
  /* 'CMatrix:979'   sin(q2+(-2)*th)-c2*dpsi*L*ml2*sin(q1+q2+(-2)*th)+(-2)* ... */
  /* 'CMatrix:980'   dpsi*H2yz*sin(phi+q1+q2+(-2)*th)-c2*dpsi*L*ml2*sin(2*phi+ ... */
  /* 'CMatrix:981'   q1+q2+(-2)*th)+dpsi*H2xx*sin(2*(phi+q1+q2-th))-dpsi* ... */
  /* 'CMatrix:982'   H2yy*sin(2*(phi+q1+q2-th))-c2^2*dpsi*ml2*sin(2*(phi+ ... */
  /* 'CMatrix:983'   q1+q2-th))+(-8)*c2*dq1*l1*ml2*sin(q2)*sin(th)+dpsi*H2xx* ... */
  /* 'CMatrix:984'   sin(2*(phi+q1+q2+th))-dpsi*H2yy*sin(2*(phi+q1+q2+th))- ... */
  /* 'CMatrix:985'   c2^2*dpsi*ml2*sin(2*(phi+q1+q2+th))+(-2)*dth*(c2*l1*ml2*cos( ... */
  /* 'CMatrix:986'   q2-th)+c2*L*ml2*cos(q1+q2-th)+2*H2yz*cos(phi+q1+q2+(-1) ... */
  /* 'CMatrix:987'   *th)+c2*L*ml2*cos(2*phi+q1+q2-th)+c2*l1*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:988'   q1+q2-th)-H2xx*cos(2*phi+2*q1+2*q2-th)+H2yy*cos( ... */
  /* 'CMatrix:989'   2*phi+2*q1+2*q2-th)+c2^2*ml2*cos(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:990'   th)+2*H2zz*cos(th)+2*c2^2*ml2*cos(th)+c2*l1*ml2*cos(q2+th)+c2* ... */
  /* 'CMatrix:991'   L*ml2*cos(q1+q2+th)+(-2)*H2yz*cos(phi+q1+q2+th)+c2*L*ml2*cos(2* ... */
  /* 'CMatrix:992'   phi+q1+q2+th)+c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx*cos(2* ... */
  /* 'CMatrix:993'   phi+2*q1+2*q2+th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2*cos(2* ... */
  /* 'CMatrix:994'   phi+2*q1+2*q2+th)+2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2* ... */
  /* 'CMatrix:995'   phi+2*q1+2*q2-th)+(-2)*H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2* ... */
  /* 'CMatrix:996'   phi+2*q1+2*q2+th))-c2*dpsi*l1*ml2*sin(q2+2*th)-c2* ... */
  /* 'CMatrix:997'   dpsi*L*ml2*sin(q1+q2+2*th)+2*dpsi*H2yz*sin(phi+q1+q2+2*th)+(-1) ... */
  /* 'CMatrix:998'   *c2*dpsi*L*ml2*sin(q1+q2+2*(phi+th))-c2*dpsi*l1*ml2*sin( ... */
  /* 'CMatrix:999'   q2+2*(phi+q1+th))); */
  /* 'CMatrix:1000' C87=c2*l1*ml2*sin(q2)*(dphi+dq1-dpsi*sin(th)); */
  /* 'CMatrix:1001' C88=0; */
  /* 'CMatrix:45' C11_83 = zeros(8, 3); */
  /* 'CMatrix:46' C14_88 = [C14, C15, C16, C17, C18;... */
  /* 'CMatrix:47'           C24, C25, C26, C27, C28;... */
  /* 'CMatrix:48'           C34, C35, C36, C37, C38;... */
  /* 'CMatrix:49'           C44, C45, C46, C47, C48;... */
  /* 'CMatrix:50'           C54, C55, C56, C57, C58;... */
  /* 'CMatrix:51'           C64, C65, C66, C67, C68;... */
  /* 'CMatrix:52'           C74, C75, C76, C77, C78;... */
  /* 'CMatrix:53'           C84, C85, C86, C87, C88]; */
  /* 'CMatrix:55' CM = [C11_83, C14_88]; */
  /* :  Gv = GVector(q, HexaConstants, ArmConstants); */
  /* 'GVector:4' g = 9.80665; */
  /* 'GVector:6' mb  = HexaConstants.Mass; */
  /* 'GVector:7' ml1 = ArmConstants.Mass1; */
  /* 'GVector:8' ml2 = ArmConstants.Mass2; */
  /* 'GVector:10' L   = ArmConstants.Hexa_to_joint_L; */
  /* 'GVector:12' l1  = ArmConstants.l1_dim(1); */
  /* 'GVector:14' c1  = ArmConstants.MC1; */
  /* 'GVector:15' c2  = ArmConstants.MC2; */
  /* 'GVector:17' phi = xi(4); */
  /* 'GVector:18' th  = xi(5); */
  /* 'GVector:20' q1   = xi(7); */
  /* 'GVector:21' q2   = xi(8); */
  /* 'GVector:23' Gv=[0,... */
  /* 'GVector:24'     0,... */
  /* 'GVector:25'     g*(mb+ml1+ml2),... */
  /* 'GVector:26'     -g*cos(th)*(-L*(ml1+ml2)*sin(phi)-(c1*ml1+l1*ml2)*sin(phi+q1)-c2*ml2*sin(phi+q1+q2)),... */
  /* 'GVector:27'     g*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+q1+q2))*sin(th),... */
  /* 'GVector:28'     0,... */
  /* 'GVector:29'     -g*cos(th)*(-(c1*ml1+l1*ml2)*sin(phi+q1)-c2*ml2*sin(phi+q1+q2)),... */
  /* 'GVector:30'     c2*g*ml2*cos(th)*sin(phi+q1+q2)]'; */
  /* :  ginv = DM; */
  /* :  fx = DM\( -CM*dq - Gv ); */
  k_a = std::sin(D56_tmp_tmp);
  l_a = std::sin(D56_tmp_tmp_1);
  m_a = std::cos(D56_tmp_tmp_6);
  n_a = std::cos(D56_tmp_tmp_7);
  o_a = std::cos(D46_tmp_tmp_6);
  p_a = std::cos(D56_tmp_tmp_8);
  q_a = std::cos(D56_tmp_tmp_9);
  r_a = std::cos(D46_tmp_tmp_7);
  s_a = std::cos(D46_tmp_tmp_8);
  t_a = std::cos(D46_tmp_tmp_9);
  u_a = std::cos(D56_tmp_tmp_2);
  v_a = std::cos(D56_tmp_tmp_4);
  w_a = std::cos(D46_tmp_tmp_a);
  x_a = std::cos(D46_tmp_tmp_b);
  y_a = std::cos(D56_tmp_tmp_5);
  ab_a = std::cos(D56_tmp_tmp_0);
  D46_tmp_n = std::sin(D56_tmp_tmp_3);
  D46_tmp_q = std::sin(ginv_tmp_tmp);
  D46_tmp_tmp_6 = -2.0 * rtu_InBus1_Positions[4];
  D46_tmp_s = std::sin(D56_tmp_tmp_1 + D46_tmp_tmp_6);
  D46_tmp_v = D46_tmp_tmp * 2.0;
  D46_tmp_w = std::sin(D46_tmp_v);
  D46_tmp_x = D46_tmp_tmp_0 * 2.0;
  tmp = std::sin(D46_tmp_x);
  tmp_0 = std::sin((-rtu_InBus1_Positions[3] + rtu_InBus1_Positions[4]) * 2.0);
  tmp_1 = (rtu_InBus1_Positions[3] + rtu_InBus1_Positions[4]) * 2.0;
  tmp_2 = std::sin(tmp_1);
  tmp_3 = D46_tmp_tmp_1 * 2.0;
  tmp_4 = std::sin(tmp_3);
  tmp_5 = D46_tmp_tmp_2 * 2.0;
  tmp_6 = std::sin(tmp_5);
  tmp_7 = std::sin(tmp_1 + rtu_InBus1_Positions[6]);
  tmp_8 = D15_tmp_tmp + D46_tmp_tmp_6;
  tmp_9 = std::cos(tmp_8);
  tmp_a = D15_tmp_tmp_0 + D46_tmp_tmp_6;
  tmp_b = std::cos(tmp_a);
  tmp_c = std::cos(D46_tmp_v);
  D46_tmp_x = std::cos(D46_tmp_x);
  tmp_d = std::cos(tmp_3);
  tmp_5 = std::cos(tmp_5);
  tmp_e = D15_tmp_tmp + ginv_tmp_tmp_0;
  D15_tmp_tmp = std::cos(tmp_e);
  D15_tmp_tmp_0 += ginv_tmp_tmp_0;
  D46_tmp_tmp = std::cos(D15_tmp_tmp_0);
  D46_tmp_v = std::sin(D46_tmp_v + rtu_InBus1_Positions[7]);
  D46_tmp_tmp_0 = std::sin(D46_tmp_tmp_6 + rtu_InBus1_Positions[6]);
  tmp_8 = std::sin(tmp_8);
  tmp_a = std::sin(tmp_a);
  D56_tmp_tmp_3 = std::sin(D56_tmp_tmp_3 + D46_tmp_tmp_6);
  D46_tmp_tmp_1 = std::sin((rtu_InBus1_Positions[3] - rtu_InBus1_Positions[4]) *
    2.0);
  D46_tmp_tmp_2 = std::sin(ginv_tmp_tmp_0 + rtu_InBus1_Positions[6]);
  tmp_e = std::sin(tmp_e);
  D15_tmp_tmp_0 = std::sin(D15_tmp_tmp_0);
  tmp_1 = std::sin(tmp_1 + smax_tmp);
  tmp_3 = std::sin(tmp_3 + rtu_InBus1_Positions[7]);
  D46_tmp_tmp_7 = std::sin(D46_tmp_tmp_6 + rtu_InBus1_Positions[7]);
  D46_tmp_tmp_6 = std::sin(smax_tmp + D46_tmp_tmp_6);
  D46_tmp_tmp_8 = std::sin(ginv_tmp_tmp_0 + rtu_InBus1_Positions[7]);
  smax_tmp = std::sin(smax_tmp + ginv_tmp_tmp_0);
  D46_tmp_tmp_9 = std::cos(ginv_tmp_tmp_0);
  D46_tmp_tmp_a = std::cos(rtu_InBus1_Positions[5]);
  D46_tmp_tmp_b = std::cos(rtu_InBus1_Positions[4]);
  D56_tmp_tmp_1 = std::sin(rtu_InBus1_Positions[3]);
  D56_tmp_tmp = ((rtu_InBus1_Positions[3] - rtu_InBus1_Positions[5]) +
                 rtu_InBus1_Positions[6]) + rtu_InBus1_Positions[7];
  D56_tmp_tmp_9 = std::cos(D56_tmp_tmp);
  D56_tmp_tmp_6 = ((rtu_InBus1_Positions[3] + rtu_InBus1_Positions[5]) +
                   rtu_InBus1_Positions[6]) + rtu_InBus1_Positions[7];
  D56_tmp_tmp_0 = std::cos(D56_tmp_tmp_6);
  D56_tmp_tmp_2 = std::cos(rtu_InBus1_Positions[5]);
  D56_tmp_tmp_4 = std::sin(rtu_InBus1_Positions[4]);
  D56_tmp_tmp_7 = std::cos(rtu_InBus1_Positions[6]);
  D56_tmp_tmp_8 = std::cos(rtu_InBus1_Positions[3]);
  D56_tmp_tmp_5 = std::sin(rtu_InBus1_Positions[5]);
  ginv_tmp_tmp_0 = std::sin(rtu_InBus1_Positions[7]);
  ginv_tmp_tmp = std::cos(rtu_InBus1_Positions[5]);
  tmp_f = std::cos(rtu_InBus1_Positions[7]);
  tmp_g = std::sin(rtu_InBus1_Positions[4]);
  tmp_h = std::sin(rtu_InBus1_Positions[3]);
  tmp_i = std::cos(rtu_InBus1_Positions[7]);
  tmp_j = std::sin(rtu_InBus1_Positions[5]);
  tmp_k = std::cos(rtu_InBus1_Positions[5]);
  tmp_l = std::sin(rtu_InBus1_Positions[7]);
  tmp_m = std::sin(rtu_InBus1_Positions[4]);
  tmp_n = std::sin(rtu_InBus1_Positions[6]);
  tmp_o = std::sin(rtu_InBus1_Positions[3]);
  tmp_p = std::sin(rtu_InBus1_Positions[5]);
  tmp_q = std::sin(rtu_InBus1_Positions[7]);
  tmp_r = std::cos(rtu_InBus1_Positions[5]);
  tmp_s = std::cos(rtu_InBus1_Positions[7]);
  tmp_t = std::sin(rtu_InBus1_Positions[4]);
  tmp_u = std::cos(rtu_InBus1_Positions[3]);
  tmp_v = std::cos(rtu_InBus1_Positions[7]);
  tmp_w = std::sin(rtu_InBus1_Positions[5]);
  tmp_x = std::cos(rtu_InBus1_Positions[5]);
  tmp_y = std::sin(rtu_InBus1_Positions[7]);
  tmp_z = std::sin(rtu_InBus1_Positions[4]);
  tmp_10 = std::cos(rtu_InBus1_Positions[3]);
  tmp_11 = std::sin(rtu_InBus1_Positions[5]);
  tmp_12 = std::sin(rtu_InBus1_Positions[6]);
  tmp_13 = std::cos(rtu_InBus1_Positions[5]);
  tmp_14 = std::cos(rtu_InBus1_Positions[6]);
  tmp_15 = std::sin(rtu_InBus1_Positions[4]);
  tmp_16 = std::sin(rtu_InBus1_Positions[3]);
  tmp_17 = std::cos(rtu_InBus1_Positions[6]);
  tmp_18 = std::sin(rtu_InBus1_Positions[5]);
  tmp_19 = std::cos(rtu_InBus1_Positions[5]);
  tmp_1a = std::sin(rtu_InBus1_Positions[6]);
  tmp_1b = std::sin(rtu_InBus1_Positions[4]);
  tmp_1c = std::sin(rtu_InBus1_Positions[3]);
  tmp_1d = std::cos(rtu_InBus1_Positions[5]);
  tmp_1e = std::sin(rtu_InBus1_Positions[6]);
  tmp_1f = std::cos(rtu_InBus1_Positions[6]);
  tmp_1g = std::sin(rtu_InBus1_Positions[5]);
  tmp_1h = std::sin(rtu_InBus1_Positions[4]);
  tmp_1i = std::cos(rtu_InBus1_Positions[3]);
  tmp_1j = std::cos(rtu_InBus1_Positions[5]);
  tmp_1k = std::cos(rtu_InBus1_Positions[6]);
  tmp_1l = std::sin(rtu_InBus1_Positions[5]);
  tmp_1m = std::sin(rtu_InBus1_Positions[6]);
  tmp_1n = std::sin(rtu_InBus1_Positions[4]);
  tmp_1o = std::cos(rtu_InBus1_Positions[3]);
  tmp_1p = std::cos(rtu_InBus1_Positions[4]);
  tmp_1q = std::sin(rtu_InBus1_Positions[5]);
  tmp_1r = std::cos(rtu_InBus1_Positions[5]);
  tmp_1s = std::cos(rtu_InBus1_Positions[4]);
  tmp_1t = std::cos(rtu_InBus1_Positions[5]);
  tmp_1u = std::cos(rtu_InBus1_Positions[4]);
  tmp_1v = std::cos(rtu_InBus1_Positions[5]);
  tmp_1w = std::cos(rtu_InBus1_Positions[4]);
  tmp_1x = std::sin(rtu_InBus1_Positions[3]);
  tmp_1y = std::cos(rtu_InBus1_Positions[5]);
  tmp_1z = std::cos(rtu_InBus1_Positions[3]);
  tmp_20 = std::sin(rtu_InBus1_Positions[4]);
  tmp_21 = std::cos(rtu_InBus1_Positions[3]);
  tmp_22 = std::cos(rtu_InBus1_Positions[4]);
  tmp_23 = std::sin(rtu_InBus1_Positions[5]);
  tmp_24 = std::cos(rtu_InBus1_Positions[5]);
  tmp_25 = std::sin(rtu_InBus1_Positions[3]);
  tmp_26 = std::cos(rtu_InBus1_Positions[3]);
  tmp_27 = std::sin(rtu_InBus1_Positions[5]);
  tmp_28 = std::sin(rtu_InBus1_Positions[4]);
  tmp_29 = std::cos(rtu_InBus1_Positions[3]);
  tmp_2a = std::cos(rtu_InBus1_Positions[5]);
  tmp_2b = std::sin(rtu_InBus1_Positions[3]);
  tmp_2c = std::sin(rtu_InBus1_Positions[5]);
  tmp_2d = std::sin(rtu_InBus1_Positions[4]);
  tmp_2e = std::sin(rtu_InBus1_Positions[6]);
  tmp_2f = std::cos(rtu_InBus1_Positions[5]);
  tmp_2g = std::sin(rtu_InBus1_Positions[3]);
  tmp_2h = std::cos(rtu_InBus1_Positions[3]);
  tmp_2i = std::sin(rtu_InBus1_Positions[5]);
  tmp_2j = std::sin(rtu_InBus1_Positions[4]);
  tmp_2k = std::cos(rtu_InBus1_Positions[6]);
  tmp_2l = std::cos(rtu_InBus1_Positions[3]);
  tmp_2m = std::cos(rtu_InBus1_Positions[5]);
  tmp_2n = std::sin(rtu_InBus1_Positions[3]);
  tmp_2o = std::sin(rtu_InBus1_Positions[5]);
  tmp_2p = std::sin(rtu_InBus1_Positions[4]);
  tmp_2q = std::cos(rtu_InBus1_Positions[3]);
  tmp_2r = std::cos(rtu_InBus1_Positions[5]);
  tmp_2s = std::sin(rtu_InBus1_Positions[3]);
  tmp_2t = std::sin(rtu_InBus1_Positions[5]);
  tmp_2u = std::sin(rtu_InBus1_Positions[4]);
  tmp_2v = std::cos(rtu_InBus1_Positions[3]);
  tmp_2w = std::sin(rtu_InBus1_Positions[5]);
  tmp_2x = std::sin(rtu_InBus1_Positions[6]);
  tmp_2y = std::cos(rtu_InBus1_Positions[5]);
  tmp_2z = std::cos(rtu_InBus1_Positions[6]);
  tmp_30 = std::sin(rtu_InBus1_Positions[4]);
  tmp_31 = std::sin(rtu_InBus1_Positions[3]);
  tmp_32 = std::cos(rtu_InBus1_Positions[6]);
  tmp_33 = std::sin(rtu_InBus1_Positions[5]);
  tmp_34 = std::cos(rtu_InBus1_Positions[5]);
  tmp_35 = std::sin(rtu_InBus1_Positions[6]);
  tmp_36 = std::sin(rtu_InBus1_Positions[4]);
  tmp_37 = std::sin(rtu_InBus1_Positions[3]);
  tmp_38 = std::cos(rtu_InBus1_Positions[5]);
  tmp_39 = std::sin(rtu_InBus1_Positions[6]);
  tmp_3a = std::cos(rtu_InBus1_Positions[6]);
  tmp_3b = std::sin(rtu_InBus1_Positions[5]);
  tmp_3c = std::sin(rtu_InBus1_Positions[4]);
  tmp_3d = std::cos(rtu_InBus1_Positions[3]);
  tmp_3e = std::cos(rtu_InBus1_Positions[5]);
  tmp_3f = std::cos(rtu_InBus1_Positions[6]);
  tmp_3g = std::sin(rtu_InBus1_Positions[5]);
  tmp_3h = std::sin(rtu_InBus1_Positions[6]);
  tmp_3i = std::sin(rtu_InBus1_Positions[4]);
  tmp_3j = std::cos(rtu_InBus1_Positions[5]);
  tmp_3k = std::cos(rtu_InBus1_Positions[6]);
  tmp_3l = std::cos(rtu_InBus1_Positions[4]);
  tmp_3m = std::sin(rtu_InBus1_Positions[3]);
  tmp_3n = std::cos(rtu_InBus1_Positions[4]);
  tmp_3o = std::sin(rtu_InBus1_Positions[3]);
  tmp_3p = std::sin(rtu_InBus1_Positions[3]);
  tmp_3q = std::sin(rtu_InBus1_Positions[6]);
  tmp_3r = std::sin(rtu_InBus1_Positions[3]);
  tmp_3s = std::sin(rtu_InBus1_Positions[6]);
  tmp_3t = std::cos(rtu_InBus1_Positions[4]);
  tmp_3u = std::cos(rtu_InBus1_Positions[4]);
  tmp_3v = std::sin(rtu_InBus1_Positions[3]);
  tmp_3w = std::cos(rtu_InBus1_Positions[4]);
  tmp_3x = std::sin(rtu_InBus1_Positions[3]);
  tmp_3y = std::sin(rtu_InBus1_Positions[6]);
  tmp_3z = std::sin(rtu_InBus1_Positions[4]);
  tmp_40 = std::sin(rtu_InBus1_Positions[3]);
  tmp_41 = std::sin(rtu_InBus1_Positions[6]);
  tmp_42 = std::sin(rtu_InBus1_Positions[4]);
  tmp_43 = std::sin(rtu_InBus1_Positions[3]);
  tmp_44 = std::sin(rtu_InBus1_Positions[6]);
  tmp_45 = std::sin(rtu_InBus1_Positions[4]);
  tmp_46 = std::sin(rtu_InBus1_Positions[3]);
  tmp_47 = std::sin(rtu_InBus1_Positions[6]);
  tmp_48 = std::sin(rtu_InBus1_Positions[4]);
  tmp_49 = std::sin(rtu_InBus1_Positions[3]);
  tmp_4a = std::sin(rtu_InBus1_Positions[4]);
  tmp_4b = std::sin(rtu_InBus1_Positions[3]);
  tmp_4c = std::sin(rtu_InBus1_Positions[4]);
  tmp_4d = std::sin(rtu_InBus1_Positions[3]);
  tmp_4e = std::sin(rtu_InBus1_Positions[4]);
  tmp_4f = std::sin(rtu_InBus1_Positions[3]);
  tmp_4g = std::sin(rtu_InBus1_Positions[5]);
  tmp_4h = std::cos(rtu_InBus1_Positions[6]);
  tmp_4i = std::sin(rtu_InBus1_Positions[4]);
  tmp_4j = std::sin(rtu_InBus1_Positions[4]);
  tmp_4k = std::cos(rtu_InBus1_Positions[3]);
  tmp_4l = std::cos(rtu_InBus1_Positions[5]);
  tmp_4m = std::cos(rtu_InBus1_Positions[4]);
  tmp_4n = std::sin(rtu_InBus1_Positions[6]);
  tmp_4o = std::cos(rtu_InBus1_Positions[4]);
  tmp_4p = std::sin(rtu_InBus1_Positions[6]);
  tmp_4q = std::cos(rtu_InBus1_Positions[4]);
  tmp_4r = std::sin(rtu_InBus1_Positions[6]);
  tmp_4s = std::sin(rtu_InBus1_Positions[7]);
  tmp_4t = std::sin(rtu_InBus1_Positions[4]);
  tmp_4u = std::sin(rtu_InBus1_Positions[4]);
  tmp_4v = std::cos(rtu_InBus1_Positions[6]);
  tmp_4w = std::cos(rtu_InBus1_Positions[7]);
  tmp_4x = std::sin(rtu_InBus1_Positions[4]);
  tmp_4y = std::sin(rtu_InBus1_Positions[5]);
  tmp_4z = std::cos(rtu_InBus1_Positions[6]);
  tmp_50 = std::sin(rtu_InBus1_Positions[7]);
  tmp_51 = std::sin(rtu_InBus1_Positions[4]);
  tmp_52 = std::sin(rtu_InBus1_Positions[6]);
  tmp_53 = std::cos(rtu_InBus1_Positions[7]);
  tmp_54 = std::sin(rtu_InBus1_Positions[4]);
  tmp_55 = std::sin(rtu_InBus1_Positions[3]);
  tmp_56 = std::sin(rtu_InBus1_Positions[5]);
  tmp_57 = std::sin(rtu_InBus1_Positions[4]);
  tmp_58 = std::cos(rtu_InBus1_Positions[5]);
  tmp_59 = std::cos(rtu_InBus1_Positions[4]);
  tmp_5a = std::sin(rtu_InBus1_Positions[3]);
  tmp_5b = std::cos(rtu_InBus1_Positions[4]);
  tmp_5c = std::sin(rtu_InBus1_Positions[3]);
  tmp_5d = std::sin(rtu_InBus1_Positions[4]);
  tmp_5e = std::cos(rtu_InBus1_Positions[3]);
  tmp_5f = std::sin(rtu_InBus1_Positions[5]);
  tmp_5g = std::sin(rtu_InBus1_Positions[4]);
  tmp_5h = std::cos(rtu_InBus1_Positions[5]);
  tmp_5i = std::cos(rtu_InBus1_Positions[4]);
  tmp_5j = std::sin(rtu_InBus1_Positions[4]);
  tmp_5k = std::cos(rtu_InBus1_Positions[5]);
  tmp_5l = std::cos(rtu_InBus1_Positions[4]);
  tmp_5m = std::sin(rtu_InBus1_Positions[5]);
  tmp_5n = std::sin(rtu_InBus1_Positions[3]);
  tmp_5o = std::cos(D56_tmp_tmp - rtu_InBus1_Positions[4]);
  tmp_5p = std::cos(D56_tmp_tmp_6 - rtu_InBus1_Positions[4]);
  tmp_5q = std::cos(D56_tmp_tmp + rtu_InBus1_Positions[4]);
  tmp_5r = std::cos(D56_tmp_tmp_6 + rtu_InBus1_Positions[4]);
  D56_tmp_tmp = std::sin(D56_tmp_tmp);
  D56_tmp_tmp_6 = std::sin(D56_tmp_tmp_6);
  tmp_5s = std::sin(rtu_InBus1_Positions[5]);
  tmp_5t = std::sin(rtu_InBus1_Positions[4]);
  tmp_5u = std::cos(rtu_InBus1_Positions[5]);
  tmp_5v = std::sin(rtu_InBus1_Positions[3]);
  tmp_5w = std::cos(rtu_InBus1_Positions[3]);
  tmp_5x = std::sin(rtu_InBus1_Positions[5]);
  tmp_5y = std::sin(rtu_InBus1_Positions[4]);
  tmp_5z = std::sin(rtu_InBus1_Positions[3]);
  tmp_60 = std::sin(rtu_InBus1_Positions[5]);
  tmp_61 = std::sin(rtu_InBus1_Positions[6]);
  tmp_62 = std::cos(rtu_InBus1_Positions[5]);
  tmp_63 = std::cos(rtu_InBus1_Positions[6]);
  tmp_64 = std::sin(rtu_InBus1_Positions[4]);
  tmp_65 = std::cos(rtu_InBus1_Positions[3]);
  tmp_66 = std::cos(rtu_InBus1_Positions[6]);
  tmp_67 = std::sin(rtu_InBus1_Positions[5]);
  tmp_68 = std::cos(rtu_InBus1_Positions[5]);
  tmp_69 = std::sin(rtu_InBus1_Positions[6]);
  tmp_6a = std::sin(rtu_InBus1_Positions[4]);
  tmp_6b = std::cos(rtu_InBus1_Positions[5]);
  tmp_6c = std::cos(rtu_InBus1_Positions[3]);
  tmp_6d = std::cos(rtu_InBus1_Positions[4]);
  tmp_6e = std::cos(rtu_InBus1_Positions[4]);
  tmp_6f = std::sin(rtu_InBus1_Positions[5]);
  tmp_6g = std::cos(rtu_InBus1_Positions[4]);
  tmp_6h = std::sin(rtu_InBus1_Positions[5]);
  tmp_6i = std::cos(rtu_InBus1_Positions[4]);
  tmp_6j = std::sin(rtu_InBus1_Positions[5]);
  tmp_6k = std::sin(rtu_InBus1_Positions[3]);
  tmp_6l = std::cos(rtu_InBus1_Positions[3]);
  tmp_6m = std::sin(rtu_InBus1_Positions[5]);
  tmp_6n = std::sin(rtu_InBus1_Positions[4]);
  tmp_6o = std::cos(rtu_InBus1_Positions[5]);
  tmp_6p = std::cos(rtu_InBus1_Positions[4]);
  tmp_6q = std::cos(rtu_InBus1_Positions[4]);
  tmp_6r = std::sin(rtu_InBus1_Positions[3]);
  tmp_6s = std::sin(rtu_InBus1_Positions[4]);
  tmp_6t = std::cos(rtu_InBus1_Positions[6]);
  tmp_6u = std::sin(rtu_InBus1_Positions[4]);
  tmp_6v = std::sin(rtu_InBus1_Positions[4]);
  tmp_6w = std::cos(rtu_InBus1_Positions[3]);
  tmp_6x = std::cos(rtu_InBus1_Positions[5]);
  tmp_6y = std::cos(rtu_InBus1_Positions[4]);
  tmp_6z = std::sin(rtu_InBus1_Positions[6]);
  tmp_70 = std::sin(rtu_InBus1_Positions[4]);
  tmp_71 = std::sin(rtu_InBus1_Positions[4]);
  tmp_72 = std::sin(rtu_InBus1_Positions[5]);
  tmp_73 = std::sin(rtu_InBus1_Positions[4]);
  tmp_74 = std::sin(rtu_InBus1_Positions[4]);
  tmp_75 = std::cos(rtu_InBus1_Positions[6]);
  tmp_76 = std::sin(rtu_InBus1_Positions[4]);
  tmp_77 = std::sin(rtu_InBus1_Positions[5]);
  tmp_78 = std::sin(rtu_InBus1_Positions[3]);
  tmp_79 = std::sin(rtu_InBus1_Positions[4]);
  tmp_7a = std::sin(rtu_InBus1_Positions[6]);
  tmp_7b = std::sin(rtu_InBus1_Positions[4]);
  tmp_7c = std::cos(rtu_InBus1_Positions[5]);
  tmp_7d = std::cos(rtu_InBus1_Positions[4]);
  tmp_7e = std::sin(rtu_InBus1_Positions[5]);
  tmp_7f = std::sin(rtu_InBus1_Positions[5]);
  tmp_7g = std::sin(rtu_InBus1_Positions[4]);
  tmp_7h = std::cos(rtu_InBus1_Positions[5]);
  tmp_7i = std::sin(rtu_InBus1_Positions[5]);
  tmp_7j = std::sin(rtu_InBus1_Positions[4]);
  tmp_7k = std::cos(rtu_InBus1_Positions[5]);
  tmp_7l = std::sin(rtu_InBus1_Positions[5]);
  tmp_7m = std::sin(rtu_InBus1_Positions[4]);
  tmp_7n = std::sin(rtu_InBus1_Positions[3]);
  tmp_7o = std::sin(rtu_InBus1_Positions[5]);
  tmp_7p = std::sin(rtu_InBus1_Positions[6]);
  tmp_7q = std::cos(rtu_InBus1_Positions[5]);
  tmp_7r = std::cos(rtu_InBus1_Positions[6]);
  tmp_7s = std::sin(rtu_InBus1_Positions[4]);
  tmp_7t = std::cos(rtu_InBus1_Positions[3]);
  tmp_7u = std::cos(rtu_InBus1_Positions[6]);
  tmp_7v = std::sin(rtu_InBus1_Positions[5]);
  tmp_7w = std::cos(rtu_InBus1_Positions[5]);
  tmp_7x = std::sin(rtu_InBus1_Positions[6]);
  tmp_7y = std::sin(rtu_InBus1_Positions[4]);
  tmp_7z = std::cos(rtu_InBus1_Positions[5]);
  tmp_80 = std::sin(rtu_InBus1_Positions[4]);
  tmp_81 = std::sin(rtu_InBus1_Positions[5]);
  tmp_82 = std::cos(rtu_InBus1_Positions[4]);
  tmp_83 = std::cos(rtu_InBus1_Positions[4]);
  tmp_84 = std::cos(rtu_InBus1_Positions[3]);
  tmp_85 = std::cos(rtu_InBus1_Positions[4]);
  tmp_86 = std::sin(rtu_InBus1_Positions[3]);
  tmp_87 = std::sin(rtu_InBus1_Positions[4]);
  tmp_88 = std::cos(rtu_InBus1_Positions[3]);
  tmp_89 = std::cos(rtu_InBus1_Positions[4]);
  tmp_8a = std::sin(rtu_InBus1_Positions[4]);
  tmp_8b = std::sin(rtu_InBus1_Positions[4]);
  tmp_8c = std::sin(rtu_InBus1_Positions[3]);
  tmp_8d = std::sin(rtu_InBus1_Positions[4]);
  tmp_8e = std::cos(rtu_InBus1_Positions[4]);
  tmp_8f = std::cos(rtu_InBus1_Positions[4]);
  tmp_8g = std::sin(rtu_InBus1_Positions[4]);
  tmp_8h = std::cos(rtu_InBus1_Positions[4]);
  tmp_8i = std::sin(rtu_InBus1_Positions[4]);
  tmp_8j = std::sin(rtu_InBus1_Positions[6]);
  tmp_8k = std::sin(rtu_InBus1_Positions[7]);
  tmp_8l = std::cos(rtu_InBus1_Positions[4]);
  tmp_8m = std::cos(rtu_InBus1_Positions[4]);
  tmp_8n = std::cos(rtu_InBus1_Positions[4]);
  tmp_8o = std::cos(rtu_InBus1_Positions[4]);
  tmp_8p = std::cos(rtu_InBus1_Positions[4]);
  tmp_8q = std::cos(rtu_InBus1_Positions[4]);
  tmp_8r = std::cos(rtu_InBus1_Positions[4]);
  tmp_8s = std::cos(rtu_InBus1_Positions[4]);
  tmp_8t = std::cos(rtu_InBus1_Positions[4]);
  tmp_8u = std::cos(rtu_InBus1_Positions[4]);
  tmp_8v = std::cos(rtu_InBus1_Positions[4]);
  tmp_8w = std::cos(rtu_InBus1_Positions[4]);
  tmp_8x = std::cos(rtu_InBus1_Positions[4]);
  tmp_8y = std::cos(rtu_InBus1_Positions[4]);
  tmp_8z = std::cos(rtu_InBus1_Positions[4]);
  tmp_90 = std::cos(rtu_InBus1_Positions[4]);
  tmp_91 = std::sin(rtu_InBus1_Positions[7]);
  tmp_92 = std::sin(rtu_InBus1_Positions[4]);
  tmp_93 = std::sin(rtu_InBus1_Positions[6]);
  tmp_94 = std::sin(rtu_InBus1_Positions[4]);
  tmp_95 = std::sin(rtu_InBus1_Positions[7]);
  tmp_96 = std::sin(rtu_InBus1_Positions[6]);
  tmp_97 = std::sin(rtu_InBus1_Positions[4]);
  tmp_98 = std::sin(rtu_InBus1_Positions[7]);
  tmp_99 = std::sin(rtu_InBus1_Positions[4]);
  tmp_9a = std::cos(rtu_InBus1_Positions[4]);
  tmp_9b = std::cos(rtu_InBus1_Positions[4]);
  tmp_9c = std::cos(rtu_InBus1_Positions[4]);
  tmp_9d = std::cos(rtu_InBus1_Positions[4]);
  tmp_9e = std::cos(rtu_InBus1_Positions[4]);
  tmp_9f = std::cos(rtu_InBus1_Positions[4]);
  tmp_9g = std::cos(rtu_InBus1_Positions[4]);
  tmp_9h = std::cos(rtu_InBus1_Positions[4]);
  tmp_9i = std::cos(rtu_InBus1_Positions[3]);
  tmp_9j = std::sin(rtu_InBus1_Positions[6]);
  tmp_9k = std::sin(rtu_InBus1_Positions[6]);
  tmp_9l = std::cos(rtu_InBus1_Positions[4]);
  tmp_9m = std::cos(rtu_InBus1_Positions[4]);
  tmp_9n = std::cos(rtu_InBus1_Positions[4]);
  tmp_9o = std::cos(rtu_InBus1_Positions[4]);
  tmp_9p = std::cos(rtu_InBus1_Positions[4]);
  tmp_9q = std::cos(rtu_InBus1_Positions[4]);
  tmp_9r = std::cos(rtu_InBus1_Positions[4]);
  tmp_9s = std::cos(rtu_InBus1_Positions[4]);
  tmp_9t = std::cos(rtu_InBus1_Positions[4]);
  tmp_9u = std::cos(rtu_InBus1_Positions[4]);
  tmp_9v = std::cos(rtu_InBus1_Positions[4]);
  tmp_9w = std::cos(rtu_InBus1_Positions[4]);
  tmp_9x = std::cos(rtu_InBus1_Positions[4]);
  tmp_9y = std::cos(rtu_InBus1_Positions[4]);
  tmp_9z = std::cos(rtu_InBus1_Positions[4]);
  tmp_a0 = std::cos(rtu_InBus1_Positions[4]);
  tmp_a1 = std::cos(rtu_InBus1_Positions[4]);
  tmp_a2 = std::cos(rtu_InBus1_Positions[4]);
  tmp_a3 = std::cos(rtu_InBus1_Positions[4]);
  tmp_a4 = std::cos(rtu_InBus1_Positions[4]);
  tmp_a5 = std::sin(rtu_InBus1_Positions[6]);
  tmp_a6 = std::sin(rtu_InBus1_Positions[6]);
  tmp_a7 = std::cos(rtu_InBus1_Positions[4]);
  tmp_a8 = std::cos(rtu_InBus1_Positions[4]);
  tmp_a9 = std::sin(rtu_InBus1_Positions[7]);
  tmp_aa = std::cos(rtu_InBus1_Positions[4]);
  tmp_ab = std::cos(rtu_InBus1_Positions[6]);
  tmp_ac = std::cos(rtu_InBus1_Positions[7]);
  tmp_ad = std::cos(rtu_InBus1_Positions[4]);
  tmp_ae = std::cos(rtu_InBus1_Positions[4]);
  tmp_af = std::cos(rtu_InBus1_Positions[4]);
  tmp_ag = std::cos(rtu_InBus1_Positions[4]);
  tmp_ah = std::cos(rtu_InBus1_Positions[4]);
  tmp_ai = std::cos(rtu_InBus1_Positions[4]);
  tmp_aj = std::cos(rtu_InBus1_Positions[4]);
  tmp_ak = std::cos(rtu_InBus1_Positions[4]);
  tmp_al = std::cos(rtu_InBus1_Positions[4]);
  tmp_am = std::cos(rtu_InBus1_Positions[7]);
  tmp_an = std::cos(rtu_InBus1_Positions[4]);
  tmp_ao = std::cos(rtu_InBus1_Positions[6]);
  tmp_ap = std::cos(rtu_InBus1_Positions[7]);
  tmp_aq = std::cos(rtu_InBus1_Positions[3]);
  tmp_ar = std::cos(rtu_InBus1_Positions[6]);
  tmp_as = std::sin(rtu_InBus1_Positions[6]);
  tmp_at = std::sin(rtu_InBus1_Positions[3]);
  tmp_au = std::cos(rtu_InBus1_Positions[6]);
  tmp_av = std::sin(rtu_InBus1_Positions[6]);
  tmp_aw = std::cos(rtu_InBus1_Positions[3]);
  tmp_ax = std::sin(rtu_InBus1_Positions[3]);
  tmp_ay = std::cos(rtu_InBus1_Positions[3]);
  tmp_az = std::cos(rtu_InBus1_Positions[4]);
  tmp_b0 = std::sin(rtu_InBus1_Positions[3]);
  tmp_b1 = std::cos(rtu_InBus1_Positions[6]);
  tmp_b2 = std::sin(rtu_InBus1_Positions[6]);
  tmp_b3 = std::sin(rtu_InBus1_Positions[4]);
  tmp_b4 = std::cos(rtu_InBus1_Positions[4]);
  tmp_b5 = std::cos(rtu_InBus1_Positions[6]);
  tmp_b6 = std::sin(rtu_InBus1_Positions[6]);
  tmp_b7 = std::sin(rtu_InBus1_Positions[4]);
  tmp_b8 = std::cos(rtu_InBus1_Positions[4]);
  tmp_b9 = std::sin(rtu_InBus1_Positions[4]);
  tmp_ba = std::cos(rtu_InBus1_Positions[4]);
  tmp_bb = std::sin(rtu_InBus1_Positions[4]);
  tmp_bc = std::cos(rtu_InBus1_Positions[4]);
  tmp_bd = std::sin(rtu_InBus1_Positions[4]);
  tmp_be = std::cos(rtu_InBus1_Positions[3]);
  tmp_bf = std::cos(rtu_InBus1_Positions[4]);
  tmp_bg = std::sin(rtu_InBus1_Positions[3]);
  tmp_bh = std::sin(rtu_InBus1_Positions[4]);
  tmp_bi = std::cos(rtu_InBus1_Positions[3]);
  tmp_bj = std::cos(rtu_InBus1_Positions[4]);
  tmp_bk = std::sin(rtu_InBus1_Positions[5]);
  tmp_bl = std::cos(rtu_InBus1_Positions[5]);
  tmp_bm = std::sin(rtu_InBus1_Positions[3]);
  tmp_bn = std::cos(rtu_InBus1_Positions[3]);
  tmp_bo = std::sin(rtu_InBus1_Positions[5]);
  tmp_bp = std::sin(rtu_InBus1_Positions[4]);
  tmp_bq = std::cos(rtu_InBus1_Positions[3]);
  tmp_br = std::cos(rtu_InBus1_Positions[4]);
  tmp_bs = std::sin(rtu_InBus1_Positions[5]);
  tmp_bt = std::cos(rtu_InBus1_Positions[5]);
  tmp_bu = std::sin(rtu_InBus1_Positions[3]);
  tmp_bv = std::cos(rtu_InBus1_Positions[3]);
  tmp_bw = std::sin(rtu_InBus1_Positions[5]);
  tmp_bx = std::sin(rtu_InBus1_Positions[4]);
  tmp_by = std::cos(rtu_InBus1_Positions[5]);
  tmp_bz = std::cos(rtu_InBus1_Positions[3]);
  tmp_c0 = std::cos(rtu_InBus1_Positions[4]);
  tmp_c1 = std::cos(rtu_InBus1_Positions[6]);
  tmp_c2 = std::sin(rtu_InBus1_Positions[3]);
  tmp_c3 = std::sin(rtu_InBus1_Positions[5]);
  tmp_c4 = std::cos(rtu_InBus1_Positions[3]);
  tmp_c5 = std::cos(rtu_InBus1_Positions[5]);
  tmp_c6 = std::sin(rtu_InBus1_Positions[4]);
  tmp_c7 = std::sin(rtu_InBus1_Positions[6]);
  tmp_c8 = std::cos(rtu_InBus1_Positions[3]);
  tmp_c9 = std::sin(rtu_InBus1_Positions[5]);
  tmp_ca = std::cos(rtu_InBus1_Positions[5]);
  tmp_cb = std::sin(rtu_InBus1_Positions[3]);
  tmp_cc = std::sin(rtu_InBus1_Positions[4]);
  tmp_cd = std::cos(rtu_InBus1_Positions[5]);
  tmp_ce = std::cos(rtu_InBus1_Positions[3]);
  tmp_cf = std::cos(rtu_InBus1_Positions[4]);
  tmp_cg = std::cos(rtu_InBus1_Positions[6]);
  tmp_ch = std::sin(rtu_InBus1_Positions[3]);
  tmp_ci = std::sin(rtu_InBus1_Positions[5]);
  tmp_cj = std::cos(rtu_InBus1_Positions[3]);
  tmp_ck = std::cos(rtu_InBus1_Positions[5]);
  tmp_cl = std::sin(rtu_InBus1_Positions[4]);
  tmp_cm = std::sin(rtu_InBus1_Positions[6]);
  tmp_cn = std::cos(rtu_InBus1_Positions[3]);
  tmp_co = std::sin(rtu_InBus1_Positions[5]);
  tmp_cp = std::cos(rtu_InBus1_Positions[5]);
  tmp_cq = std::sin(rtu_InBus1_Positions[3]);
  tmp_cr = std::sin(rtu_InBus1_Positions[4]);
  tmp_cs = std::cos(rtu_InBus1_Positions[3]);
  tmp_ct = std::sin(rtu_InBus1_Positions[3]);
  tmp_cu = std::sin(rtu_InBus1_Positions[3]);
  tmp_cv = std::sin(rtu_InBus1_Positions[5]);
  tmp_cw = std::cos(rtu_InBus1_Positions[3]);
  tmp_cx = std::cos(rtu_InBus1_Positions[5]);
  tmp_cy = std::sin(rtu_InBus1_Positions[4]);
  tmp_cz = std::cos(rtu_InBus1_Positions[3]);
  tmp_d0 = std::sin(rtu_InBus1_Positions[5]);
  tmp_d1 = std::cos(rtu_InBus1_Positions[5]);
  tmp_d2 = std::sin(rtu_InBus1_Positions[3]);
  tmp_d3 = std::sin(rtu_InBus1_Positions[4]);
  tmp_d4 = std::cos(rtu_InBus1_Positions[6]);
  tmp_d5 = std::sin(rtu_InBus1_Positions[3]);
  tmp_d6 = std::sin(rtu_InBus1_Positions[5]);
  tmp_d7 = std::cos(rtu_InBus1_Positions[3]);
  tmp_d8 = std::cos(rtu_InBus1_Positions[5]);
  tmp_d9 = std::sin(rtu_InBus1_Positions[4]);
  tmp_da = std::sin(rtu_InBus1_Positions[6]);
  tmp_db = std::cos(rtu_InBus1_Positions[3]);
  tmp_dc = std::sin(rtu_InBus1_Positions[5]);
  tmp_dd = std::cos(rtu_InBus1_Positions[5]);
  tmp_de = std::sin(rtu_InBus1_Positions[3]);
  tmp_df = std::sin(rtu_InBus1_Positions[4]);
  tmp_dg = std::cos(rtu_InBus1_Positions[5]);
  tmp_dh = std::sin(rtu_InBus1_Positions[3]);
  tmp_di = std::cos(rtu_InBus1_Positions[3]);
  tmp_dj = std::sin(rtu_InBus1_Positions[5]);
  tmp_dk = std::sin(rtu_InBus1_Positions[4]);
  tmp_dl = std::cos(rtu_InBus1_Positions[5]);
  tmp_dm = std::sin(rtu_InBus1_Positions[3]);
  tmp_dn = std::cos(rtu_InBus1_Positions[3]);
  tmp_do = std::sin(rtu_InBus1_Positions[5]);
  tmp_dp = std::sin(rtu_InBus1_Positions[4]);
  tmp_dq = std::cos(rtu_InBus1_Positions[3]);
  tmp_dr = std::cos(rtu_InBus1_Positions[5]);
  tmp_ds = std::sin(rtu_InBus1_Positions[3]);
  tmp_dt = std::sin(rtu_InBus1_Positions[5]);
  tmp_du = std::sin(rtu_InBus1_Positions[4]);
  tmp_dv = std::sin(rtu_InBus1_Positions[3]);
  tmp_dw = std::cos(rtu_InBus1_Positions[3]);
  tmp_dx = std::cos(rtu_InBus1_Positions[3]);
  tmp_dy = std::sin(rtu_InBus1_Positions[3]);
  tmp_dz = std::sin(rtu_InBus1_Positions[6]);
  tmp_e0 = std::sin(rtu_InBus1_Positions[3]);
  tmp_e1 = std::sin(rtu_InBus1_Positions[5]);
  tmp_e2 = std::cos(rtu_InBus1_Positions[3]);
  tmp_e3 = std::cos(rtu_InBus1_Positions[5]);
  tmp_e4 = std::sin(rtu_InBus1_Positions[4]);
  tmp_e5 = std::cos(rtu_InBus1_Positions[6]);
  tmp_e6 = std::cos(rtu_InBus1_Positions[3]);
  tmp_e7 = std::sin(rtu_InBus1_Positions[5]);
  tmp_e8 = std::cos(rtu_InBus1_Positions[5]);
  tmp_e9 = std::sin(rtu_InBus1_Positions[3]);
  tmp_ea = std::sin(rtu_InBus1_Positions[4]);
  tmp_eb = std::cos(rtu_InBus1_Positions[6]);
  tmp_ec = std::sin(rtu_InBus1_Positions[3]);
  tmp_ed = std::sin(rtu_InBus1_Positions[5]);
  tmp_ee = std::cos(rtu_InBus1_Positions[3]);
  tmp_ef = std::cos(rtu_InBus1_Positions[5]);
  tmp_eg = std::sin(rtu_InBus1_Positions[4]);
  tmp_eh = std::sin(rtu_InBus1_Positions[6]);
  tmp_ei = std::cos(rtu_InBus1_Positions[3]);
  tmp_ej = std::sin(rtu_InBus1_Positions[5]);
  tmp_ek = std::cos(rtu_InBus1_Positions[5]);
  tmp_el = std::sin(rtu_InBus1_Positions[3]);
  tmp_em = std::sin(rtu_InBus1_Positions[4]);
  tmp_en = std::cos(rtu_InBus1_Positions[5]);
  tmp_eo = std::sin(rtu_InBus1_Positions[3]);
  tmp_ep = std::cos(rtu_InBus1_Positions[3]);
  tmp_eq = std::sin(rtu_InBus1_Positions[5]);
  tmp_er = std::sin(rtu_InBus1_Positions[4]);
  tmp_es = std::sin(rtu_InBus1_Positions[6]);
  tmp_et = std::cos(rtu_InBus1_Positions[5]);
  tmp_eu = std::sin(rtu_InBus1_Positions[3]);
  tmp_ev = std::cos(rtu_InBus1_Positions[3]);
  tmp_ew = std::sin(rtu_InBus1_Positions[5]);
  tmp_ex = std::sin(rtu_InBus1_Positions[4]);
  tmp_ey = std::cos(rtu_InBus1_Positions[6]);
  tmp_ez = std::cos(rtu_InBus1_Positions[3]);
  tmp_f0 = std::cos(rtu_InBus1_Positions[5]);
  tmp_f1 = std::sin(rtu_InBus1_Positions[3]);
  tmp_f2 = std::sin(rtu_InBus1_Positions[5]);
  tmp_f3 = std::sin(rtu_InBus1_Positions[4]);
  tmp_f4 = std::cos(rtu_InBus1_Positions[6]);
  tmp_f5 = std::sin(rtu_InBus1_Positions[3]);
  tmp_f6 = std::sin(rtu_InBus1_Positions[5]);
  tmp_f7 = std::cos(rtu_InBus1_Positions[3]);
  tmp_f8 = std::cos(rtu_InBus1_Positions[5]);
  tmp_f9 = std::sin(rtu_InBus1_Positions[4]);
  tmp_fa = std::sin(rtu_InBus1_Positions[6]);
  tmp_fb = std::cos(rtu_InBus1_Positions[3]);
  tmp_fc = std::sin(rtu_InBus1_Positions[5]);
  tmp_fd = std::cos(rtu_InBus1_Positions[5]);
  tmp_fe = std::sin(rtu_InBus1_Positions[3]);
  tmp_ff = std::sin(rtu_InBus1_Positions[4]);
  tmp_fg = std::sin(rtu_InBus1_Positions[3]);
  tmp_fh = std::sin(rtu_InBus1_Positions[5]);
  tmp_fi = std::sin(rtu_InBus1_Positions[6]);
  tmp_fj = std::cos(rtu_InBus1_Positions[5]);
  tmp_fk = std::cos(rtu_InBus1_Positions[6]);
  tmp_fl = std::sin(rtu_InBus1_Positions[4]);
  tmp_fm = std::cos(rtu_InBus1_Positions[3]);
  tmp_fn = std::cos(rtu_InBus1_Positions[6]);
  tmp_fo = std::sin(rtu_InBus1_Positions[5]);
  tmp_fp = std::cos(rtu_InBus1_Positions[5]);
  tmp_fq = std::sin(rtu_InBus1_Positions[6]);
  tmp_fr = std::sin(rtu_InBus1_Positions[4]);
  tmp_fs = std::cos(rtu_InBus1_Positions[5]);
  tmp_ft = std::sin(rtu_InBus1_Positions[3]);
  tmp_fu = std::cos(rtu_InBus1_Positions[3]);
  tmp_fv = std::sin(rtu_InBus1_Positions[5]);
  tmp_fw = std::sin(rtu_InBus1_Positions[4]);
  tmp_fx = std::sin(rtu_InBus1_Positions[3]);
  tmp_fy = std::cos(rtu_InBus1_Positions[5]);
  tmp_fz = std::sin(rtu_InBus1_Positions[6]);
  tmp_g0 = std::cos(rtu_InBus1_Positions[6]);
  tmp_g1 = std::sin(rtu_InBus1_Positions[5]);
  tmp_g2 = std::sin(rtu_InBus1_Positions[4]);
  tmp_g3 = std::cos(rtu_InBus1_Positions[3]);
  tmp_g4 = std::cos(rtu_InBus1_Positions[5]);
  tmp_g5 = std::cos(rtu_InBus1_Positions[6]);
  tmp_g6 = std::sin(rtu_InBus1_Positions[5]);
  tmp_g7 = std::sin(rtu_InBus1_Positions[6]);
  tmp_g8 = std::sin(rtu_InBus1_Positions[4]);
  tmp_g9 = std::sin(rtu_InBus1_Positions[3]);
  tmp_ga = std::cos(rtu_InBus1_Positions[6]);
  tmp_gb = std::sin(rtu_InBus1_Positions[6]);
  tmp_gc = std::cos(rtu_InBus1_Positions[3]);
  tmp_gd = std::cos(rtu_InBus1_Positions[6]);
  tmp_ge = std::sin(rtu_InBus1_Positions[6]);
  tmp_gf = std::sin(rtu_InBus1_Positions[3]);
  tmp_gg = std::cos(rtu_InBus1_Positions[3]);
  tmp_gh = std::cos(rtu_InBus1_Positions[4]);
  tmp_gi = std::cos(rtu_InBus1_Positions[4]);
  tmp_gj = std::cos(rtu_InBus1_Positions[4]);
  tmp_gk = std::cos(rtu_InBus1_Positions[4]);
  tmp_gl = std::cos(rtu_InBus1_Positions[4]);
  tmp_gm = std::cos(rtu_InBus1_Positions[4]);
  tmp_gn = std::sin(rtu_InBus1_Positions[6]);
  tmp_go = std::sin(rtu_InBus1_Positions[6]);
  tmp_gp = std::cos(rtu_InBus1_Positions[4]);
  tmp_gq = std::cos(rtu_InBus1_Positions[4]);
  tmp_gr = std::sin(rtu_InBus1_Positions[7]);
  tmp_gs = std::sin(rtu_InBus1_Positions[7]);
  tmp_gt = std::sin(rtu_InBus1_Positions[6]);
  tmp_gu = std::sin(rtu_InBus1_Positions[4]);
  tmp_gv = std::sin(rtu_InBus1_Positions[6]);
  tmp_gw = std::sin(rtu_InBus1_Positions[6]);
  tmp_gx = std::cos(rtu_InBus1_Positions[4]);
  tmp_gy = std::cos(rtu_InBus1_Positions[4]);
  tmp_gz = std::cos(rtu_InBus1_Positions[4]);
  tmp_h0 = std::cos(rtu_InBus1_Positions[4]);
  tmp_h1 = std::cos(rtu_InBus1_Positions[4]);
  tmp_h2 = std::sin(rtu_InBus1_Positions[6]);
  tmp_h3 = std::sin(rtu_InBus1_Positions[6]);
  tmp_h4 = std::sin(rtu_InBus1_Positions[7]);
  tmp_h5 = std::sin(rtu_InBus1_Positions[4]);
  tmp_h6 = std::cos(rtu_InBus1_Positions[4]);
  tmp_h7 = std::cos(rtu_InBus1_Positions[4]);
  tmp_h8 = std::cos(rtu_InBus1_Positions[4]);
  tmp_h9 = std::cos(rtu_InBus1_Positions[4]);
  tmp_ha = std::cos(rtu_InBus1_Positions[4]);
  tmp_hb = std::sin(rtu_InBus1_Positions[7]);
  tmp_hc = std::sin(rtu_InBus1_Positions[7]);
  tmp_hd = std::sin(rtu_InBus1_Positions[4]);
  tmp_he = std::sin(rtu_InBus1_Positions[7]);
  tmp_hf = std::sin(rtu_InBus1_Positions[7]);
  tmp_hg = std::sin(rtu_InBus1_Positions[4]);
  tmp_hh = std::cos(rtu_InBus1_Positions[3]);
  tmp_hi = std::cos(rtu_InBus1_Positions[4]);
  tmp_hj = std::cos(rtu_InBus1_Positions[4]);
  tmp_hk = std::sin(rtu_InBus1_Positions[7]);
  tmp_hl = std::sin(rtu_InBus1_Positions[7]);
  tmp_hm = std::sin(rtu_InBus1_Positions[4]);
  tmp_hn = std::cos(rtu_InBus1_Positions[4]);
  tmp_ho = std::cos(rtu_InBus1_Positions[4]);
  tmp_hp = std::sin(rtu_InBus1_Positions[7]);
  tmp_hq = std::sin(rtu_InBus1_Positions[4]);
  tmp_hz = rtP_ArmConstants.MC2 * rtu_InBus1_Velocities[7] *
    rtP_ArmConstants.Mass2;
  tmp_i0 = 2.0 * rtu_InBus1_Velocities[4];
  tmp_i1 = -2.0 * rtu_InBus1_Velocities[6];
  tmp_i2 = 2.0 * rtu_InBus1_Velocities[6];
  tmp_hr[24] = -((((((((D14_tmp * tmp_f + D14_tmp_0) * ginv_tmp_tmp * tmp_g +
                       D14_tmp * D56_tmp_tmp_5 * ginv_tmp_tmp_0) * D56_tmp_tmp_8
                      + ((D14_tmp * tmp_i + D14_tmp_0) * tmp_j - D14_tmp * tmp_k
    * tmp_l * tmp_m) * tmp_h) * (tmp_i2 * D56_tmp_tmp_7) + ((2.0 * D56_tmp_tmp_2
    * D15_tmp_0 * D56_tmp_tmp_4 + (D56_tmp_tmp_9 - D56_tmp_tmp_0)) * tmp_hz +
    ((D14_tmp_2 * D56_tmp_tmp_1 + D34_tmp_0) + D34_tmp_1) * (tmp_i0 *
    D46_tmp_tmp_a * D46_tmp_tmp_b))) + (((D14_tmp * tmp_s + D14_tmp_0) * tmp_r *
    tmp_t + D14_tmp * tmp_p * tmp_q) * tmp_o + (-(D14_tmp * tmp_v + D14_tmp_0) *
    tmp_w + D14_tmp * tmp_x * tmp_y * tmp_z) * tmp_u) * (tmp_i1 * tmp_n)) +
                   ((((D14_tmp_0 * tmp_14 + D14_tmp_2) + D14_tmp_3) * tmp_13 *
                     tmp_15 + (D14_tmp_0 * tmp_12 + D14_tmp_4) * tmp_11) * (2.0 *
    tmp_10) + (((D14_tmp_0 * tmp_17 + D14_tmp_2) + D14_tmp_3) * tmp_18 -
               (D14_tmp_0 * tmp_1a + D14_tmp_4) * tmp_19 * tmp_1b) * (2.0 *
    tmp_16)) * rtu_InBus1_Velocities[3]) + (((D14_tmp_0 * tmp_1e + D14_tmp_4) *
    tmp_1d - ((D14_tmp_0 * tmp_1f + D14_tmp_2) + D14_tmp_3) * tmp_1g * tmp_1h) *
    (2.0 * tmp_1c) + (((D14_tmp_0 * tmp_1k + D14_tmp_2) + D14_tmp_3) * tmp_1j +
                      (D14_tmp_0 * tmp_1m + D14_tmp_4) * tmp_1l * tmp_1n) *
    (-2.0 * tmp_1i)) * rtu_InBus1_Velocities[5]) * 0.5);
  tmp_hr[32] = -((((((D14_tmp_2 * tmp_1o + D15_tmp_1) + D15_tmp_2) *
                    rtu_InBus1_Velocities[5] * tmp_1p * tmp_1q + tmp_hz * tmp_1r
                    * tmp_1s * D34_tmp) + rtu_InBus1_Velocities[6] * tmp_1t *
                   tmp_1u * D37_tmp) + ((D14_tmp_2 * tmp_1x + D34_tmp_0) +
    D34_tmp_1) * (rtu_InBus1_Velocities[3] * tmp_1v * tmp_1w)) + ((D14_tmp_2 *
    tmp_1z + D15_tmp_1) + D15_tmp_2) * (rtu_InBus1_Velocities[4] * tmp_1y) *
                 tmp_20);
  D46_tmp_tmp_a = D46_tmp_f * rtu_InBus1_Velocities[7] * rtP_ArmConstants.Mass2;
  tmp_hr[40] = -(((((((D14_tmp_0 * tmp_2z + D14_tmp_2) + D14_tmp_3) * tmp_2y *
                     tmp_30 + (D14_tmp_0 * tmp_2x + D14_tmp_4) * tmp_2w) * (2.0 *
    tmp_2v) + (-((D14_tmp_0 * tmp_32 + D14_tmp_2) + D14_tmp_3) * tmp_33 +
               (D14_tmp_0 * tmp_35 + D14_tmp_4) * tmp_34 * tmp_36) * (-2.0 *
    tmp_31)) * rtu_InBus1_Velocities[5] + ((((D14_tmp_2 * tmp_21 + D15_tmp_1) +
    D15_tmp_2) * tmp_i0 * tmp_22 * tmp_23 + ((tmp_26 * tmp_27 * tmp_28 + -tmp_24
    * tmp_25) * smax + (tmp_2b * tmp_2c * tmp_2d + tmp_29 * tmp_2a) * s) *
    D46_tmp_tmp_a) + (((-tmp_2h * tmp_2i * tmp_2j + tmp_2f * tmp_2g) *
                       -(D14_tmp_0 * tmp_2e + D14_tmp_4) + (tmp_2n * tmp_2o *
    tmp_2p + tmp_2l * tmp_2m) * (D14_tmp_0 * tmp_2k)) + (tmp_2s * tmp_2t *
    tmp_2u + tmp_2q * tmp_2r) * D14_tmp_3) * tmp_i1)) + (((D14_tmp_0 * tmp_39 +
    D14_tmp_4) * tmp_38 - ((D14_tmp_0 * tmp_3a + D14_tmp_2) + D14_tmp_3) *
    tmp_3b * tmp_3c) * (2.0 * tmp_37) + (((D14_tmp_0 * tmp_3f + D14_tmp_2) +
    D14_tmp_3) * tmp_3e + (D14_tmp_0 * tmp_3h + D14_tmp_4) * tmp_3g * tmp_3i) *
    (-2.0 * tmp_3d)) * rtu_InBus1_Velocities[3]) * 0.5);
  D46_tmp_tmp_b = rtP_ArmConstants.MC2 * rtu_InBus1_Velocities[4] *
    rtP_ArmConstants.Mass2;
  D56_tmp_tmp_1 = rtu_InBus1_Velocities[3] + rtu_InBus1_Velocities[6];
  D56_tmp_tmp_9 = rtP_ArmConstants.MC1 * rtu_InBus1_Velocities[4] *
    rtP_ArmConstants.Mass1;
  D56_tmp_tmp_0 = rtu_InBus1_Velocities[4] * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  D56_tmp_tmp_2 = 2.0 * rtu_InBus1_Velocities[5];
  D56_tmp_tmp_4 = rtP_ArmConstants.MC2 * rtu_InBus1_Velocities[3] *
    rtP_ArmConstants.Mass2;
  D56_tmp_tmp_7 = rtu_InBus1_Velocities[6] + rtu_InBus1_Velocities[7];
  D56_tmp_tmp_8 = D56_tmp_tmp_7 * 2.0 + rtu_InBus1_Velocities[3];
  D56_tmp_tmp_5 = -2.0 * rtu_InBus1_Velocities[5];
  ginv_tmp_tmp_0 = D56_tmp_tmp_1 + rtu_InBus1_Velocities[7];
  ginv_tmp_tmp = D14_tmp_0 * D56_tmp_tmp_5;
  tmp_f = D14_tmp_0 * rtu_InBus1_Velocities[4];
  tmp_g = D46_tmp_tmp_f * rtu_InBus1_Velocities[5];
  tmp_h = D46_tmp_d * rtu_InBus1_Velocities[5];
  tmp_i = -2.0 * rtu_InBus1_Velocities[3];
  tmp_hr[48] = -(((((((((((((((((tmp_f * tmp_3k * tmp_3l * tmp_3m +
    D46_tmp_tmp_b * s * tmp_3n * tmp_3o) + tmp_g * rtP_ArmConstants.Mass1 *
    tmp_3p * tmp_3q) + D56_tmp_tmp_2 * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2 * tmp_3r * tmp_3s) + D56_tmp_tmp_9 * tmp_3t * a) +
    D56_tmp_tmp_0 * tmp_3u * a) + tmp_h * rtP_ArmConstants.Mass2 * tmp_3v * smax)
    + D46_tmp_tmp_b * tmp_3w * D34_tmp) + D46_tmp_z * rtu_InBus1_Velocities[3] *
    rtP_ArmConstants.Mass1 * tmp_3x * tmp_3y * tmp_3z) + D46_tmp_z *
    rtu_InBus1_Velocities[6] * rtP_ArmConstants.Mass1 * tmp_40 * tmp_41 * tmp_42)
                        + tmp_i * rtP_ArmConstants.l1_dim *
                        rtP_ArmConstants.Mass2 * tmp_43 * tmp_44 * tmp_45) +
                       tmp_i1 * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2
                       * tmp_46 * tmp_47 * tmp_48) + D46_tmp_f *
                      rtu_InBus1_Velocities[3] * rtP_ArmConstants.Mass2 * tmp_49
                      * smax * tmp_4a) + D46_tmp_f * rtu_InBus1_Velocities[6] *
                     rtP_ArmConstants.Mass2 * tmp_4b * smax * tmp_4c) +
                    D46_tmp_tmp_a * tmp_4d * smax * tmp_4e) * tmp_3j +
                   ((D56_tmp_tmp_1 - rtu_InBus1_Velocities[5] * tmp_4i) *
                    (D14_tmp_0 * tmp_4h) + (ginv_tmp_tmp_0 -
    rtu_InBus1_Velocities[5] * tmp_4j) * D14_tmp_3) * (2.0 * tmp_4f * tmp_4g)) +
                  ((((((D56_tmp_tmp_9 * tmp_4m * tmp_4n + D56_tmp_tmp_0 * tmp_4o
                        * tmp_4p) + D46_tmp_tmp_b * tmp_4q * smax) -
                      D56_tmp_tmp_4 * tmp_4r * tmp_4s * tmp_4t) - (D56_tmp_tmp_2
    - D56_tmp_tmp_8 * tmp_4u) * D14_tmp_3) + ((D56_tmp_tmp_1 * 2.0 * D14_tmp_0 +
    D56_tmp_tmp_4 * tmp_4w) * tmp_4x + ginv_tmp_tmp) * tmp_4v) * tmp_4l +
                   (((D56_tmp_tmp_5 * tmp_51 + D56_tmp_tmp_8) * smax +
                     rtu_InBus1_Velocities[3] * tmp_4z * tmp_50) * D14_tmp +
                    ((D56_tmp_tmp_1 - rtu_InBus1_Velocities[5] * tmp_54) *
                     (D14_tmp_0 * 2.0) + D56_tmp_tmp_4 * tmp_53) * tmp_52) *
                   tmp_4y) * tmp_4k) * 0.5);
  D46_tmp_tmp_a = 2.0 * s;
  tmp_hr[56] = -(((((ginv_tmp_tmp_0 * tmp_5j - rtu_InBus1_Velocities[5]) *
                    D46_tmp_tmp_a + rtu_InBus1_Velocities[4] * tmp_5i * smax) *
                   tmp_5h + (ginv_tmp_tmp_0 - rtu_InBus1_Velocities[5] * tmp_5g)
                   * (2.0 * tmp_5f * smax)) * tmp_5e + (((rtu_InBus1_Velocities
    [4] * s * tmp_59 * tmp_5a + rtu_InBus1_Velocities[4] * tmp_5b * D34_tmp) +
    (rtu_InBus1_Velocities[5] - ginv_tmp_tmp_0 * tmp_5d) * (2.0 * tmp_5c * smax))
    * tmp_58 + D46_tmp_tmp_a * tmp_55 * tmp_56 * (ginv_tmp_tmp_0 -
    rtu_InBus1_Velocities[5] * tmp_57))) * (0.5 * rtP_ArmConstants.MC2 *
    rtP_ArmConstants.Mass2));
  D46_tmp_tmp_a = D15_tmp_1 + D15_tmp_2;
  D56_tmp_tmp_9 = D46_tmp_tmp_a * rtu_InBus1_Velocities[6];
  tmp_hr[25] = -(((((D14_tmp_0 * tmp_63 + D14_tmp_2) + D14_tmp_3) * tmp_62 *
                   tmp_64 + (D14_tmp_0 * tmp_61 + D14_tmp_4) * tmp_60) * tmp_5z
                  + (-((D14_tmp_0 * tmp_66 + D14_tmp_2) + D14_tmp_3) * tmp_67 +
                     (D14_tmp_0 * tmp_69 + D14_tmp_4) * tmp_68 * tmp_6a) *
                  tmp_65) * rtu_InBus1_Velocities[5] + ((((((((tmp_5o - tmp_5p)
    - tmp_5q) + tmp_5r) + 2.0 * D56_tmp_tmp) + 2.0 * D56_tmp_tmp_6) * (-0.25 *
    rtP_ArmConstants.MC2 * rtu_InBus1_Velocities[7] * rtP_ArmConstants.Mass2) +
    (((D14_tmp_2 * tmp_5n + D34_tmp_0) + D34_tmp_1) * (rtu_InBus1_Velocities[4] *
    tmp_5l * tmp_5m) + -rtu_InBus1_Velocities[6] * tmp_5k * D37_tmp)) +
    D56_tmp_tmp_9 * tmp_5s * tmp_5t) + (((D14_tmp_2 * tmp_5w + D15_tmp_1) +
    D15_tmp_2) * tmp_5x * tmp_5y + ((D14_tmp_2 * tmp_5v + D34_tmp_0) + D34_tmp_1)
    * -tmp_5u) * rtu_InBus1_Velocities[3]));
  tmp_hr[33] = -((((((D14_tmp_2 * tmp_6c + D15_tmp_1) + D15_tmp_2) *
                    (-rtu_InBus1_Velocities[5] * tmp_6b) * tmp_6d + tmp_hz *
                    tmp_6e * tmp_6f * D34_tmp) + rtu_InBus1_Velocities[6] *
                   tmp_6g * tmp_6h * D37_tmp) + ((D14_tmp_2 * tmp_6k + D34_tmp_0)
    + D34_tmp_1) * (rtu_InBus1_Velocities[3] * tmp_6i * tmp_6j)) + ((D14_tmp_2 *
    tmp_6l + D15_tmp_1) + D15_tmp_2) * rtu_InBus1_Velocities[4] * tmp_6m *
                 tmp_6n);
  D56_tmp_tmp = (tmp_i2 + rtu_InBus1_Velocities[3]) * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2 + D46_tmp_tmp_f * D56_tmp_tmp_1 *
    rtP_ArmConstants.Mass1;
  D56_tmp_tmp_6 = rtu_InBus1_Velocities[3] * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  D56_tmp_tmp_0 = -0.5 * rtP_ArmConstants.MC2 * rtP_ArmConstants.Mass2;
  tmp_j = 4.0 * rtu_InBus1_Velocities[5];
  tmp_k = -4.0 * rtu_InBus1_Velocities[6];
  tmp_l = -4.0 * rtu_InBus1_Velocities[7];
  tmp_hr[41] = -((((((((((-3.0 * rtu_InBus1_Velocities[3] + tmp_k) + tmp_l) +
                        rtu_InBus1_Velocities[3] * D46_tmp_tmp_9) + tmp_j *
                       tmp_74) * (D56_tmp_tmp_0 * s) + (-rtu_InBus1_Velocities[5]
    * tmp_73 + rtu_InBus1_Velocities[3]) * (D46_tmp_tmp_5 * D14_tmp_1)) +
                     ((ginv_tmp_tmp * tmp_76 + D56_tmp_tmp) + D14 * D14 *
                      D56_tmp_tmp_6) * tmp_75) * tmp_72 +
                    (((rtu_InBus1_Velocities[5] - D56_tmp_tmp_1 * tmp_70) *
                      (D14_tmp_0 * tmp_6z) + rtu_InBus1_Velocities[4] *
                      rtP_ArmConstants.Hexa_to_joint_L * D14_tmp_1 * tmp_6y) +
                     (rtu_InBus1_Velocities[5] - ginv_tmp_tmp_0 * tmp_71) *
                     D14_tmp_4) * (2.0 * tmp_6x)) * -tmp_6w +
                   ((((rtu_InBus1_Velocities[5] - D56_tmp_tmp_1 * tmp_6u) *
                      (D14_tmp_0 * tmp_6t) + (-rtu_InBus1_Velocities[3] * tmp_6s
    + rtu_InBus1_Velocities[5]) * D14_tmp_2) + (rtu_InBus1_Velocities[5] -
    ginv_tmp_tmp_0 * tmp_6v) * D14_tmp_3) * tmp_6r + (tmp_f * D15_tmp * tmp_6p +
    D46_tmp_tmp_b * D15_tmp_0 * tmp_6q)) * (-2.0 * tmp_6o)) + ((((ginv_tmp_tmp *
    tmp_7b + D56_tmp_tmp) + D18 * D18 * D56_tmp_tmp_6) * tmp_7a +
    ((D56_tmp_tmp_5 * tmp_79 + D56_tmp_tmp_8) + D17 * D17 *
     rtu_InBus1_Velocities[3]) * D14_tmp_4) * tmp_78 + (-rtu_InBus1_Velocities[3]
    * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * D15_tmp * (D15 * D15) -
    D56_tmp_tmp_4 * D15_tmp_0 * (D16 * D16))) * tmp_77) * 0.5);
  tmp_hr[49] = -((((D14_tmp_0 * tmp_7r + D14_tmp_3) * tmp_7q * tmp_7s +
                   (D14_tmp_0 * tmp_7p + D14_tmp_4) * tmp_7o) * tmp_7n +
                  ((D14_tmp_0 * tmp_7x + D14_tmp_4) * tmp_7w * tmp_7y +
                   -(D14_tmp_0 * tmp_7u + D14_tmp_3) * tmp_7v) * tmp_7t) *
                 rtu_InBus1_Velocities[5] + ((((rtu_InBus1_Velocities[4] *
    tmp_7d * tmp_7e * D37_tmp + -rtu_InBus1_Velocities[3] * tmp_7c * D37_tmp) +
    D46_tmp_tmp_a * rtu_InBus1_Velocities[3] * tmp_7f * tmp_7g) - (tmp_7h *
    D34_tmp - D15_tmp_0 * tmp_7i * tmp_7j) * tmp_hz) + (D46_tmp_tmp_a * tmp_7l *
    tmp_7m + D37_tmp * -tmp_7k) * rtu_InBus1_Velocities[6]));
  tmp_hr[57] = -(((((ginv_tmp_tmp_0 - rtu_InBus1_Velocities[4]) * D46_tmp_6 +
                    D56_tmp_tmp_2 * D15_tmp_0) - (ginv_tmp_tmp_0 +
    rtu_InBus1_Velocities[4]) * D46_tmp_8) * tmp_81 + (ginv_tmp_tmp_0 -
    rtu_InBus1_Velocities[5] * tmp_80) * (2.0 * tmp_7z * D34_tmp)) *
                 D56_tmp_tmp_0);
  tmp_hr[26] = -((((D14_tmp_2 * tmp_84 + D15_tmp_1) + D15_tmp_2) *
                  rtu_InBus1_Velocities[3] * tmp_85 + (tmp_hz * D15_tmp_0 *
    tmp_82 + D56_tmp_tmp_9 * tmp_83)) - ((D14_tmp_2 * tmp_86 + D34_tmp_0) +
    D34_tmp_1) * rtu_InBus1_Velocities[4] * tmp_87);
  tmp_hr[34] = -(((((D14_tmp_2 * tmp_88 + D15_tmp_1) + D15_tmp_2) *
                   rtu_InBus1_Velocities[4] * tmp_89 - tmp_hz * D34_tmp * tmp_8a)
                  + D37_tmp * -rtu_InBus1_Velocities[6] * tmp_8b) - ((D14_tmp_2 *
    tmp_8c + D34_tmp_0) + D34_tmp_1) * rtu_InBus1_Velocities[3] * tmp_8d);
  tmp_hr[42] = -0.0;
  tmp_hr[50] = -((ginv_tmp_tmp_0 * rtP_ArmConstants.MC2 * rtP_ArmConstants.Mass2
                  * D15_tmp_0 * tmp_8f + D14_tmp_0 * D56_tmp_tmp_1 * D15_tmp *
                  tmp_8e) - D37_tmp * rtu_InBus1_Velocities[4] * tmp_8g);
  tmp_hr[58] = -((ginv_tmp_tmp_0 * D15_tmp_0 * tmp_8h - rtu_InBus1_Velocities[4]
                  * D34_tmp * tmp_8i) * D14_tmp);
  tmp_hr[27] = -(-rtu_InBus1_Velocities[6] * rtP_ArmConstants.Hexa_to_joint_L *
                 D14_tmp_0 * tmp_8j - (D56_tmp_tmp_7 *
    rtP_ArmConstants.Hexa_to_joint_L * smax + rtu_InBus1_Velocities[7] *
    rtP_ArmConstants.l1_dim * tmp_8k) * D14_tmp);
  D46_tmp_tmp_a = D56_tmp_j * D46_tmp_1;
  D46_tmp_tmp_b = rtP_ArmConstants.Inertia1[0] * D56_tmp_7;
  D56_tmp_tmp = rtP_ArmConstants.Inertia1[4] * D56_tmp_7;
  D56_tmp_tmp_9 = D47_tmp_1 * D56_tmp_7;
  D56_tmp_tmp_6 = D47_tmp_2 * D56_tmp_7;
  D56_tmp_tmp_0 = D46_tmp_j * s_a;
  D56_tmp_tmp_4 = D46_tmp_tmp_3 * D14_tmp_1 + (rtP_HexaConstants.Inertia[4] -
    rtP_HexaConstants.Inertia[8]);
  D56_tmp_tmp_7 = (((((((((D56_tmp_tmp_4 * q_a + ginv_tmp_0 * r_a) +
    D46_tmp_tmp_a) + D46_tmp_k * m_a) + D46_tmp_l * m_a) - D46_tmp_tmp_b) +
                      D56_tmp_tmp) + D56_tmp_tmp_9) + D56_tmp_tmp_6) +
                   D56_tmp_tmp_0) + D46_tmp_m * t_a;
  D56_tmp_tmp_8 = D56_tmp_k * D46_tmp_2;
  ginv_tmp_tmp = D46_tmp_tmp_3 * 2.0;
  tmp_f = D46_tmp_g * 2.0;
  tmp_m = D46_tmp_h * 2.0;
  tmp_n = rtP_HexaConstants.Inertia[4] * k_a;
  tmp_o = rtP_HexaConstants.Inertia[8] * k_a;
  tmp_p = D56_tmp_h * k_a;
  tmp_q = D56_tmp_i * k_a;
  tmp_r = rtP_ArmConstants.Inertia1[0] * D46_tmp_p;
  tmp_s = rtP_ArmConstants.Inertia1[4] * D46_tmp_p;
  tmp_t = D47_tmp_1 * D46_tmp_p;
  tmp_u = D47_tmp_2 * D46_tmp_p;
  tmp_v = rtP_ArmConstants.Inertia2[0] * D46_tmp_r;
  tmp_w = rtP_ArmConstants.Inertia2[4] * D46_tmp_r;
  tmp_x = D47_tmp * D46_tmp_r;
  D56_tmp_tmp_7 += D56_tmp_tmp_8;
  tmp_y = D46_tmp_m * u_a;
  tmp_z = D46_tmp_j * v_a;
  tmp_10 = rtP_ArmConstants.Inertia2[0] * D56_tmp_8;
  tmp_11 = rtP_ArmConstants.Inertia2[4] * D56_tmp_8;
  tmp_12 = D47_tmp * D56_tmp_8;
  tmp_13 = 2.0 * rtP_ArmConstants.Inertia1[8];
  tmp_14 = 2.0 * rtP_ArmConstants.Inertia2[8];
  tmp_15 = tmp_f * rtP_ArmConstants.Mass1;
  tmp_16 = tmp_m * rtP_ArmConstants.Mass2;
  tmp_17 = D46_tmp_i * 2.0 * rtP_ArmConstants.Mass2;
  tmp_18 = D56_tmp_l * D46_tmp_3;
  tmp_19 = rtP_ArmConstants.Inertia1[0] * D56_tmp_9;
  tmp_1a = rtP_ArmConstants.Inertia1[4] * D56_tmp_9;
  tmp_1b = D47_tmp_1 * D56_tmp_9;
  tmp_1c = D47_tmp_2 * D56_tmp_9;
  tmp_1d = D46_tmp_j * w_a;
  tmp_1e = D56_tmp_m * D46_tmp_4;
  tmp_1f = D46_tmp_j * ab_a;
  tmp_1g = rtP_ArmConstants.Inertia2[0] * D56_tmp_a;
  tmp_1h = rtP_ArmConstants.Inertia2[4] * D56_tmp_a;
  tmp_1i = D47_tmp * D56_tmp_a;
  tmp_1j = D56_tmp_n * D46_tmp_5;
  tmp_1k = ginv_tmp_5 * D56_tmp_1;
  tmp_1l = D56_tmp_o * D46_tmp_6;
  tmp_1m = ginv_tmp_3 * D56_tmp_2;
  tmp_1n = D56_tmp_p * D46_tmp_7;
  tmp_1o = ginv_tmp_5 * D56_tmp_5;
  tmp_1p = D56_tmp_q * D46_tmp_8;
  tmp_1q = ginv_tmp_3 * D56_tmp_6;
  D56_tmp_tmp_7 = ((((D56_tmp_tmp_7 + tmp_y) + tmp_z) - tmp_10) + tmp_11) +
    tmp_12;
  tmp_y = 2.0 * rtP_HexaConstants.Inertia[0];
  tmp_1r = ginv_tmp_tmp * rtP_ArmConstants.Mass1;
  ginv_tmp_tmp *= rtP_ArmConstants.Mass2;
  tmp_1s = rtP_HexaConstants.Inertia[4] * n_a;
  tmp_1t = rtP_HexaConstants.Inertia[8] * n_a;
  tmp_1u = D56_tmp_h * n_a;
  tmp_1v = D56_tmp_i * n_a;
  tmp_1w = D46_tmp_k * o_a;
  tmp_1x = D46_tmp_l * o_a;
  tmp_1y = D46_tmp_k * p_a;
  tmp_1z = D46_tmp_l * p_a;
  tmp_20 = D46_tmp_m * x_a;
  tmp_21 = D46_tmp_m * y_a;
  tmp_22 = D56_tmp_f * D46_tmp_a + D56_tmp_g * D46_tmp_c;
  tmp_23 = D46_tmp_j * D46_tmp_q;
  tmp_hr[35] = -(((((((((((((((((((((((((((((((((((((((tmp_13 * tmp_8l +
    D56_tmp_tmp_7) + tmp_14 * tmp_8m) + tmp_y * tmp_8n) + tmp_15 * tmp_8o) +
    tmp_1r * tmp_8p) + tmp_16 * tmp_8q) + ginv_tmp_tmp * tmp_8r) + tmp_17 *
    tmp_8s) + tmp_1s) - tmp_1t) + tmp_1u) + tmp_1v) + tmp_1w) + tmp_1x) + tmp_18)
    + tmp_1y) + tmp_1z) - tmp_19) + tmp_1a) + tmp_1b) + tmp_1c) + tmp_1d) +
    tmp_20) + tmp_1e) + tmp_21) + tmp_1f) - tmp_1g) + tmp_1h) + tmp_1i) + tmp_1j)
    + tmp_1k) + tmp_1l) + tmp_1m) + tmp_1n) + tmp_1o) + tmp_1p) + tmp_1q) *
                  -rtu_InBus1_Velocities[5] + (((((((((((((((tmp_22 + tmp_n) -
    tmp_o) + tmp_p) + tmp_q) - tmp_r) + tmp_s) + tmp_t) + tmp_u) + D46_tmp_k *
    l_a) + D46_tmp_l * l_a) - tmp_v) + tmp_w) + tmp_x) + D46_tmp_m * D46_tmp_n)
    + tmp_23) * tmp_i0) * 0.25);
  tmp_24 = -2.0 * rtu_InBus1_Velocities[4];
  tmp_25 = tmp_24 * D46_tmp_tmp_3;
  tmp_26 = -4.0 * rtu_InBus1_Velocities[4];
  tmp_27 = -4.0 * rtP_ArmConstants.MC1;
  tmp_28 = tmp_27 * rtu_InBus1_Velocities[4] * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  tmp_29 = tmp_26 * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim;
  tmp_29 *= rtP_ArmConstants.Mass2;
  tmp_2a = -4.0 * rtP_ArmConstants.MC2;
  tmp_2b = tmp_2a * rtu_InBus1_Velocities[4];
  tmp_2c = tmp_2b * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2;
  tmp_2b = tmp_2b * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  tmp_2d = tmp_24 * rtP_HexaConstants.Inertia[4];
  tmp_2e = tmp_i0 * rtP_HexaConstants.Inertia[8];
  tmp_2f = tmp_25 * rtP_ArmConstants.Mass1;
  tmp_25 *= rtP_ArmConstants.Mass2;
  tmp_2g = D56_tmp_tmp_2 * rtP_ArmConstants.Inertia1[3];
  tmp_2h = tmp_i0 * rtP_ArmConstants.Inertia1[0];
  tmp_2i = tmp_24 * rtP_ArmConstants.Inertia1[4];
  tmp_2j = D46_tmp_tmp_c * rtu_InBus1_Velocities[4] * rtP_ArmConstants.Mass1;
  tmp_2k = tmp_24 * D46_tmp_i * rtP_ArmConstants.Mass2;
  tmp_2l = D56_tmp_tmp_2 * rtP_ArmConstants.Inertia2[3];
  tmp_2m = D56_tmp_tmp_2 * rtP_ArmConstants.Inertia1[6];
  tmp_2n = D56_tmp_tmp_2 * rtP_ArmConstants.Inertia2[6];
  tmp_2o = tmp_2d * q_a;
  tmp_2p = tmp_2e * q_a;
  tmp_2q = tmp_2f * q_a;
  tmp_2r = tmp_25 * q_a;
  tmp_2s = tmp_26 * rtP_ArmConstants.Inertia1[7];
  tmp_2t = tmp_2s * D46_tmp_1;
  tmp_2u = tmp_2g * tmp_c;
  tmp_2v = tmp_28 * m_a;
  tmp_2w = tmp_29 * m_a;
  tmp_2x = tmp_2h * D56_tmp_7;
  tmp_2y = tmp_2i * D56_tmp_7;
  tmp_2z = tmp_2j * D56_tmp_7;
  tmp_30 = tmp_2k * D56_tmp_7;
  tmp_31 = tmp_26 * rtP_ArmConstants.Inertia2[7];
  tmp_32 = tmp_31 * D46_tmp_2;
  tmp_33 = tmp_2l * D46_tmp_x;
  tmp_34 = tmp_2c * u_a;
  tmp_35 = tmp_2b * s_a;
  tmp_36 = tmp_j * rtP_ArmConstants.Inertia2[3] * D46_tmp_c;
  tmp_37 = tmp_2n * tmp_b;
  tmp_38 = ((tmp_j * rtP_ArmConstants.Inertia1[3] * D46_tmp_a + tmp_36) + tmp_2m
            * tmp_9) + tmp_37;
  tmp_39 = ((((((((((((((((((tmp_38 + tmp_2o) + tmp_2p) + tmp_2q) + tmp_2r) +
    tmp_28 * r_a) + tmp_29 * r_a) + tmp_2t) + tmp_2u) + tmp_2v) + tmp_2w) +
                   tmp_2x) + tmp_2y) + tmp_2z) + tmp_30) + tmp_35) + tmp_2c *
              t_a) + tmp_32) + tmp_33) + tmp_34;
  tmp_3a = tmp_2b * v_a;
  tmp_3b = tmp_i0 * rtP_ArmConstants.Inertia2[0];
  tmp_3c = tmp_3b * D56_tmp_8;
  tmp_3d = tmp_24 * rtP_ArmConstants.Inertia2[4];
  tmp_3e = D46_tmp_tmp_d * rtu_InBus1_Velocities[4] * rtP_ArmConstants.Mass2;
  tmp_hw = _mm_mul_pd(_mm_set1_pd(-4.0), _mm_set1_pd(rtu_InBus1_Velocities[4]));
  _mm_storeu_pd(&tmp_hv[0], tmp_hw);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  tmp_3f = tmp_hv[0];
  tmp_3g = tmp_hv[1];
  tmp_3h = D46_tmp_g * -4.0;
  tmp_3i = tmp_26 * D46_tmp_tmp_3;
  tmp_3j = 4.0 * rtu_InBus1_Velocities[4];
  tmp_3k = D56_tmp_tmp_5 * D46_tmp_tmp_3;
  tmp_3l = D56_tmp_tmp_5 * rtP_ArmConstants.Inertia1[6];
  tmp_3m = D56_tmp_tmp_5 * rtP_ArmConstants.Inertia2[6];
  tmp_3n = tmp_3d * D56_tmp_8;
  tmp_3o = tmp_3e * D56_tmp_8;
  tmp_3p = -4.0 * D46_tmp_h;
  tmp_3q = -4.0 * rtu_InBus1_Velocities[5];
  tmp_3r = D56_tmp_tmp_5 * rtP_ArmConstants.Inertia1[4];
  tmp_3s = D56_tmp_tmp_5 * rtP_ArmConstants.Inertia2[4];
  tmp_3t = D56_tmp_tmp_5 * rtP_HexaConstants.Inertia[4];
  tmp_3u = tmp_3h * rtu_InBus1_Velocities[4] * rtP_ArmConstants.Mass1;
  tmp_3v = tmp_3p * rtu_InBus1_Velocities[4];
  tmp_3v *= rtP_ArmConstants.Mass2;
  tmp_3w = tmp_26 * D46_tmp_i * rtP_ArmConstants.Mass2;
  tmp_3x = tmp_2b * w_a;
  tmp_3y = tmp_2g * tmp_d;
  tmp_3z = tmp_2l * tmp_5;
  tmp_40 = tmp_3l * D15_tmp_tmp;
  tmp_41 = tmp_3m * D46_tmp_tmp;
  tmp_42 = D56_tmp_tmp_2 * rtP_ArmConstants.Inertia1[0] * D46_tmp_p;
  tmp_43 = D46_tmp_tmp_c * rtu_InBus1_Velocities[5] * rtP_ArmConstants.Mass1;
  tmp_44 = D56_tmp_tmp_5 * D46_tmp_i;
  tmp_45 = tmp_3r * D46_tmp_p;
  tmp_43 *= D46_tmp_p;
  tmp_44 = tmp_44 * rtP_ArmConstants.Mass2 * D46_tmp_p;
  tmp_46 = D56_tmp_tmp_2 * rtP_ArmConstants.Inertia2[0] * D46_tmp_r;
  tmp_47 = tmp_3s * D46_tmp_r;
  tmp_48 = D46_tmp_tmp_d * rtu_InBus1_Velocities[5] * rtP_ArmConstants.Mass2 *
    D46_tmp_r;
  tmp_39 = (((((((((((((((((((((((((((((((((((((((((((((((((tmp_39 + tmp_3a) +
    tmp_3c) + tmp_3n) + tmp_3o) + tmp_3f * rtP_ArmConstants.Inertia1[8] * tmp_8t)
    + tmp_3g * rtP_ArmConstants.Inertia2[8] * tmp_8u) + tmp_26 *
    rtP_HexaConstants.Inertia[0] * tmp_8v) + tmp_3u * tmp_8w) + tmp_3i *
    rtP_ArmConstants.Mass1 * tmp_8x) + tmp_3v * tmp_8y) + tmp_3i *
    rtP_ArmConstants.Mass2 * tmp_8z) + tmp_3w * tmp_90) + tmp_2d * n_a) + tmp_2e
    * n_a) + tmp_2f * n_a) + tmp_25 * n_a) + tmp_28 * o_a) + tmp_29 * o_a) +
    tmp_3j * rtP_ArmConstants.Inertia1[7] * D46_tmp_3) + tmp_3y) + tmp_28 * p_a)
    + tmp_29 * p_a) + tmp_2h * D56_tmp_9) + tmp_2i * D56_tmp_9) + tmp_2j *
    D56_tmp_9) + tmp_2k * D56_tmp_9) + tmp_3x) + tmp_2c * x_a) + tmp_3j *
    rtP_ArmConstants.Inertia2[7] * D46_tmp_4) + tmp_3z) + tmp_2c * y_a) + tmp_2b
    * ab_a) + tmp_3b * D56_tmp_a) + tmp_3d * D56_tmp_a) + tmp_3e * D56_tmp_a) +
    tmp_40) + tmp_41) + tmp_3t * k_a) + D56_tmp_tmp_2 *
                      rtP_HexaConstants.Inertia[8] * k_a) + tmp_3k *
                     rtP_ArmConstants.Mass1 * k_a) + tmp_3k *
                    rtP_ArmConstants.Mass2 * k_a) + tmp_42) + tmp_45) + tmp_43)
                + tmp_44) + tmp_27 * rtu_InBus1_Velocities[5] *
               rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1 * l_a)
              + tmp_3q * rtP_ArmConstants.Hexa_to_joint_L *
              rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * l_a) + tmp_46)
            + tmp_47) + tmp_48;
  tmp_3f = tmp_2a * rtu_InBus1_Velocities[5];
  tmp_3g = tmp_3f * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2 *
    D46_tmp_n;
  tmp_3f = tmp_3f * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  tmp_3i = D46_tmp_f * rtu_InBus1_Velocities[5];
  tmp_3k = tmp_3i * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  tmp_49 = rtP_ArmConstants.Inertia1[7];
  tmp_4a = D46_tmp_z * rtu_InBus1_Velocities[5] *
    rtP_ArmConstants.Hexa_to_joint_L;
  tmp_4b = D56_tmp_tmp_5 * rtP_ArmConstants.Hexa_to_joint_L;
  tmp_4c = rtP_ArmConstants.l1_dim;
  tmp_4d = D46_tmp_tmp_3 * rtu_InBus1_Velocities[5];
  tmp_4e = rtP_HexaConstants.Inertia[4] * rtu_InBus1_Velocities[5];
  tmp_4f = rtu_InBus1_Velocities[5] * rtP_HexaConstants.Inertia[8];
  tmp_4g = tmp_4d * rtP_ArmConstants.Mass1;
  tmp_4d *= rtP_ArmConstants.Mass2;
  tmp_4h = rtP_ArmConstants.Inertia1[0] * rtu_InBus1_Velocities[5];
  tmp_4i = rtP_ArmConstants.Inertia1[4] * rtu_InBus1_Velocities[5];
  tmp_4j = D46_tmp_g * rtu_InBus1_Velocities[5] * rtP_ArmConstants.Mass1;
  tmp_4k = tmp_26 * rtP_ArmConstants.Inertia1[3];
  tmp_4l = rtP_ArmConstants.Inertia2[0] * rtu_InBus1_Velocities[5];
  tmp_4m = rtP_ArmConstants.Inertia2[4] * rtu_InBus1_Velocities[5];
  tmp_4n = D46_tmp_h * rtu_InBus1_Velocities[5] * rtP_ArmConstants.Mass2;
  tmp_4o = tmp_26 * rtP_ArmConstants.Inertia2[3];
  tmp_4a *= rtP_ArmConstants.Mass1;
  tmp_4b = tmp_4b * tmp_4c * rtP_ArmConstants.Mass2;
  tmp_3i = tmp_3i * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2;
  tmp_4c = rtP_ArmConstants.Hexa_to_joint_L * smax;
  tmp_4p = D56_tmp_tmp_2 * rtP_ArmConstants.Inertia1[7];
  tmp_4q = D46_tmp_i * rtu_InBus1_Velocities[5] * rtP_ArmConstants.Mass2;
  tmp_4r = D56_tmp_tmp_2 * rtP_ArmConstants.Inertia2[7];
  tmp_49 *= D56_tmp_tmp_5;
  tmp_4s = D56_tmp_tmp_5 * rtP_ArmConstants.Inertia2[7];
  tmp_4t = tmp_3k * D46_tmp_v;
  tmp_4u = tmp_4a * D46_tmp_s;
  tmp_4v = tmp_4b * D46_tmp_s;
  tmp_4w = tmp_3i * D56_tmp_tmp_3;
  tmp_4x = tmp_4f * D46_tmp_tmp_1;
  tmp_4y = tmp_26 * rtP_ArmConstants.Inertia1[6];
  tmp_4z = tmp_4y * D46_tmp_5;
  tmp_50 = tmp_4h * D46_tmp_w;
  tmp_51 = tmp_4i * D46_tmp_w;
  tmp_52 = tmp_4j * D46_tmp_w;
  tmp_53 = tmp_4q * D46_tmp_w;
  tmp_54 = tmp_4k * D56_tmp_1;
  tmp_55 = tmp_26 * rtP_ArmConstants.Inertia2[6];
  tmp_56 = tmp_55 * D46_tmp_6;
  tmp_57 = tmp_4l * tmp;
  tmp_58 = tmp_4m * tmp;
  tmp_59 = tmp_4n * tmp;
  tmp_5a = tmp_4o * D56_tmp_2;
  tmp_5b = tmp_4e * tmp_0;
  tmp_5c = tmp_4g * tmp_0;
  tmp_5d = tmp_4d * tmp_0;
  tmp_5e = tmp_4e * tmp_2;
  tmp_5f = tmp_4f * tmp_2;
  tmp_5g = tmp_4g * tmp_2;
  tmp_5h = tmp_4d * tmp_2;
  tmp_5i = tmp_4h * tmp_4;
  tmp_5j = tmp_4i * tmp_4;
  tmp_5k = tmp_4j * tmp_4;
  tmp_5l = tmp_4l * tmp_6;
  tmp_5m = tmp_4m * tmp_6;
  tmp_5n = tmp_4n * tmp_6;
  tmp_3f *= D46_tmp_q;
  tmp_5o = tmp_49 * tmp_8;
  tmp_5p = tmp_4s * tmp_a;
  tmp_5q = 8.0 * rtP_ArmConstants.MC2 * rtu_InBus1_Velocities[7];
  tmp_5r = tmp_4p * tmp_e;
  tmp_5s = tmp_4r * D15_tmp_tmp_0;
  tmp_5t = tmp_3k * tmp_3;
  tmp_hr[43] = -(((((((((((((((((((((((((((((((((((((((((((((((tmp_39 + tmp_3g)
    + tmp_3f) + tmp_4t) + tmp_5o) + tmp_4u) + tmp_4v) + tmp_5p) + tmp_4w) +
    tmp_4x) + tmp_4z) + tmp_50) - tmp_51) - tmp_52) - tmp_53) + tmp_54) + tmp_56)
    + tmp_57) - tmp_58) - tmp_59) + tmp_5a) + (rtP_ArmConstants.l1_dim * tmp_91
    + tmp_4c) * (tmp_5q * rtP_ArmConstants.Mass2) * tmp_92) + (D14_tmp_0 *
    tmp_93 + D14_tmp_4) * (8.0 * rtu_InBus1_Velocities[6] *
    rtP_ArmConstants.Hexa_to_joint_L) * tmp_94) + tmp_5b) + tmp_5c) + tmp_5d) -
    tmp_5e) + tmp_5f) - tmp_5g) - tmp_5h) + tmp_3j * rtP_ArmConstants.Inertia1[6]
    * D46_tmp_7) + tmp_5i) - tmp_5j) - tmp_5k) + D46_tmp_i *
    -rtu_InBus1_Velocities[5] * rtP_ArmConstants.Mass2 * tmp_4) + tmp_4k *
    D56_tmp_5) + tmp_3j * rtP_ArmConstants.Inertia2[6] * D46_tmp_8) + tmp_5l) -
    tmp_5m) - tmp_5n) + tmp_4o * D56_tmp_6) + tmp_5r) + tmp_5s) + tmp_4a * tmp_7)
                    + tmp_4b * tmp_7) + tmp_3i * tmp_1) + tmp_5t) * 0.125);
  tmp_39 = -rtP_ArmConstants.MC2 * rtu_InBus1_Velocities[7];
  tmp_hr[51] = -((rtP_ArmConstants.l1_dim * tmp_95 + tmp_4c) * (tmp_39 *
    rtP_ArmConstants.Mass2) - (D14_tmp_0 * tmp_96 + D14_tmp_4) *
                 rtP_ArmConstants.Hexa_to_joint_L * (D56_tmp_tmp_1 -
    rtu_InBus1_Velocities[5] * tmp_97));
  tmp_hr[59] = -((rtP_ArmConstants.l1_dim * tmp_98 + tmp_4c) *
                 (-rtP_ArmConstants.MC2 * rtP_ArmConstants.Mass2) *
                 (ginv_tmp_tmp_0 - rtu_InBus1_Velocities[5] * tmp_99));
  tmp_g *= rtP_ArmConstants.Hexa_to_joint_L;
  tmp_g *= rtP_ArmConstants.Mass1;
  tmp_3g = D56_tmp_tmp_2 * rtP_ArmConstants.Hexa_to_joint_L;
  tmp_3g = tmp_3g * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  tmp_4k = tmp_h * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2;
  tmp_h *= rtP_ArmConstants.l1_dim;
  tmp_h *= rtP_ArmConstants.Mass2;
  tmp_4o = D56_tmp_tmp_2 * D46_tmp_tmp_3;
  tmp_5u = tmp_3j * rtP_ArmConstants.Inertia2[3];
  tmp_5v = tmp_5u * D46_tmp_c;
  tmp_5w = 4.0 * rtu_InBus1_Velocities[3];
  tmp_3j *= rtP_ArmConstants.Inertia1[3];
  tmp_5x = tmp_5w * rtP_ArmConstants.Inertia2[6];
  tmp_5y = 4.0 * rtu_InBus1_Velocities[7];
  tmp_5z = 4.0 * rtu_InBus1_Velocities[6];
  tmp_60 = ((((D56_tmp_tmp_1 * 4.0 * rtP_ArmConstants.Inertia1[6] * D15_tmp +
               tmp_3j * D46_tmp_a) + tmp_5x * D15_tmp_0) + tmp_5z *
             rtP_ArmConstants.Inertia2[6] * D15_tmp_0) + tmp_5y *
            rtP_ArmConstants.Inertia2[6] * D15_tmp_0) + tmp_5v;
  tmp_61 = tmp_4p * D46_tmp_1;
  tmp_62 = tmp_4h * D56_tmp_7;
  tmp_63 = tmp_4i * D56_tmp_7;
  tmp_64 = tmp_4j * D56_tmp_7;
  tmp_65 = tmp_4q * D56_tmp_7;
  tmp_66 = tmp_h * s_a;
  tmp_67 = tmp_4r * D46_tmp_2;
  tmp_68 = tmp_h * v_a;
  tmp_69 = tmp_4l * D56_tmp_8;
  tmp_6a = tmp_4m * D56_tmp_8;
  tmp_6b = tmp_4n * D56_tmp_8;
  tmp_6c = D56_tmp_tmp_2 * rtP_ArmConstants.Inertia1[8];
  tmp_6d = D56_tmp_tmp_2 * rtP_ArmConstants.Inertia2[8];
  tmp_6e = tmp_f * rtu_InBus1_Velocities[5] * rtP_ArmConstants.Mass1;
  tmp_6f = tmp_m * rtu_InBus1_Velocities[5] * rtP_ArmConstants.Mass2;
  tmp_6g = D56_tmp_tmp_2 * D46_tmp_i * rtP_ArmConstants.Mass2;
  tmp_6h = tmp_4o * rtP_ArmConstants.Mass1;
  tmp_4o *= rtP_ArmConstants.Mass2;
  tmp_4d = (((((((((((((((((((((((((((((((tmp_4e * q_a + tmp_60) - tmp_4f * q_a)
    + tmp_4g * q_a) + tmp_4d * q_a) + tmp_g * r_a) + tmp_3g * r_a) + tmp_61) +
    tmp_g * m_a) + tmp_3g * m_a) - tmp_62) + tmp_63) + tmp_64) + tmp_65) +
    tmp_66) + tmp_4k * t_a) + tmp_67) + tmp_4k * u_a) + tmp_68) - tmp_69) +
                       tmp_6a) + tmp_6b) + tmp_6c * tmp_9a) + tmp_6d * tmp_9b) +
                   D56_tmp_tmp_2 * rtP_HexaConstants.Inertia[0] * tmp_9c) +
                  tmp_6e * tmp_9d) + tmp_6h * tmp_9e) + tmp_6f * tmp_9f) +
               tmp_4o * tmp_9g) + tmp_6g * tmp_9h) + tmp_4e * n_a) - tmp_4f *
            n_a) + tmp_4g * n_a;
  tmp_hw = _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set_pd(2.0,
    rtP_ArmConstants.Hexa_to_joint_L), _mm_set_pd(rtP_ArmConstants.MC1,
    rtP_ArmConstants.Hexa_to_joint_L)), _mm_set1_pd(rtu_InBus1_Velocities[5])),
    _mm_set_pd(rtP_ArmConstants.Hexa_to_joint_L, rtP_ArmConstants.Mass2)),
                      _mm_set_pd(rtP_ArmConstants.Mass1, n_a));
  _mm_storeu_pd(&tmp_hv[0], tmp_hw);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  tmp_4e = tmp_hv[0];
  tmp_4f = tmp_hv[1];
  tmp_4g = -4.0 * rtu_InBus1_Velocities[3];
  tmp_4h *= D56_tmp_9;
  tmp_4i *= D56_tmp_9;
  tmp_4j *= D56_tmp_9;
  tmp_6i = tmp_4q * D56_tmp_9;
  tmp_6j = tmp_h * w_a;
  tmp_6k = tmp_4s * D46_tmp_4;
  tmp_6l = tmp_h * ab_a;
  tmp_4l *= D56_tmp_a;
  tmp_4m *= D56_tmp_a;
  tmp_4n *= D56_tmp_a;
  tmp_6m = tmp_4g * rtP_ArmConstants.Inertia1[7] * a;
  tmp_6n = tmp_k * rtP_ArmConstants.Inertia1[7] * a;
  tmp_2h *= D46_tmp_p;
  tmp_2i *= D46_tmp_p;
  tmp_2j *= D46_tmp_p;
  tmp_2k *= D46_tmp_p;
  tmp_6o = tmp_4g * rtP_ArmConstants.Inertia2[7] * D34_tmp;
  tmp_6p = tmp_k * rtP_ArmConstants.Inertia2[7] * D34_tmp;
  tmp_6q = tmp_l * rtP_ArmConstants.Inertia2[7] * D34_tmp;
  tmp_3b *= D46_tmp_r;
  tmp_3d *= D46_tmp_r;
  tmp_3e *= D46_tmp_r;
  tmp_2b *= D46_tmp_q;
  tmp_6r = tmp_2m * D46_tmp_5;
  tmp_6s = tmp_2g * D56_tmp_1;
  tmp_6t = tmp_2n * D46_tmp_6;
  tmp_6u = tmp_2l * D56_tmp_2;
  tmp_6v = tmp_3l * D46_tmp_7;
  tmp_2g *= D56_tmp_5;
  tmp_6w = tmp_3m * D46_tmp_8;
  tmp_2l *= D56_tmp_6;
  tmp_hr[28] = -(((((((((((((((((((((((((((((((((((((((((((((((tmp_4d + tmp_4e)
    + tmp_4f * o_a) + tmp_3g * o_a) + tmp_49 * D46_tmp_3) + tmp_g * p_a) +
    tmp_3g * p_a) - tmp_4h) + tmp_4i) + tmp_4j) + tmp_6i) + tmp_6j) + tmp_4k *
    x_a) + tmp_6k) + tmp_4k * y_a) + tmp_6l) - tmp_4l) + tmp_4m) + tmp_4n) +
    tmp_2d * k_a) + tmp_2e * k_a) + tmp_2f * k_a) + tmp_25 * k_a) + tmp_6m) +
    tmp_6n) + tmp_2h) + tmp_2i) + tmp_2j) + tmp_2k) + tmp_28 * l_a) + tmp_29 *
    l_a) + tmp_6o) + tmp_6p) + tmp_6q) + tmp_3b) + tmp_3d) + tmp_3e) + tmp_2c *
    D46_tmp_n) + tmp_2b) + tmp_6r) + tmp_6s) + tmp_6t) + tmp_6u) + tmp_6v) +
                    tmp_2g) + tmp_6w) + tmp_2l) * 0.25);
  tmp_25 = ginv_tmp_5 * D46_tmp_a + ginv_tmp_3 * D46_tmp_c;
  tmp_28 = D46_tmp_tmp_e * D46_tmp_q;
  tmp_29 = 2.0 * rtu_InBus1_Velocities[7];
  tmp_2c = -rtP_ArmConstants.MC1 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  tmp_2d = D67_tmp_0 * l_a;
  tmp_2e = D47_tmp_tmp_tmp * smax;
  tmp_2f = D47_tmp_tmp_tmp * D46_tmp_n;
  tmp_4d = D48_tmp * D15_tmp;
  tmp_4e = (D47_tmp + ginv_tmp_4) * D15_tmp_0;
  tmp_hr[36] = -((((((((((((((((((tmp_25 - tmp_n) + tmp_o) - tmp_p) - tmp_q) +
    tmp_r) - tmp_s) - tmp_t) - tmp_u) + D46_tmp_10 * l_a) + D46_tmp_11 * l_a) +
                        tmp_v) - tmp_w) - tmp_x) + D46_tmp_12 * D46_tmp_n) +
                    tmp_28) * rtu_InBus1_Velocities[3] + (((D47_tmp_tmp_tmp *
    tmp_9i + tmp_4d) + tmp_4e) * (-2.0 * rtu_InBus1_Velocities[7]) * D34_tmp +
    tmp_29 * rtP_ArmConstants.Inertia2[3] * D46_tmp_c)) +
                  (((((((((((((-rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * tmp_9k + (tmp_25 -
    D67_tmp * tmp_9j)) + tmp_r) - tmp_s) - tmp_t) - tmp_u) + tmp_2c * l_a) -
    tmp_2d) - tmp_2e) + tmp_v) - tmp_w) - tmp_x) - tmp_2f) + tmp_28) *
                  rtu_InBus1_Velocities[6]) * 0.5);
  tmp_n = D47_tmp_5 * r_a;
  D46_tmp_tmp_a = (tmp_n + D46_tmp_tmp_a) + D67_tmp * m_a;
  tmp_o = D67_tmp_0 * m_a;
  D46_tmp_tmp_a += tmp_o;
  D46_tmp_tmp_b = D46_tmp_tmp_a - D46_tmp_tmp_b;
  tmp_o = 4.0 * rtP_ArmConstants.Inertia1[6];
  tmp_p = 4.0 * rtP_ArmConstants.Inertia2[6];
  tmp_q = -4.0 * rtP_ArmConstants.Inertia1[7];
  tmp_25 = -4.0 * rtP_ArmConstants.Inertia2[7];
  D46_tmp_tmp_1 = (((((((((((((((((((tmp_o * tmp_9 + tmp_p * tmp_b) + ginv_tmp_5
    * tmp_c) + ginv_tmp_3 * D46_tmp_x) + D56_tmp_f * tmp_d) + D56_tmp_g * tmp_5)
    + tmp_o * D15_tmp_tmp) + tmp_p * D46_tmp_tmp) + D46_tmp_tmp_e * D46_tmp_v) +
    D46_tmp_10 * D46_tmp_tmp_0) + D46_tmp_11 * D46_tmp_tmp_0) + tmp_q * tmp_8) +
    D46_tmp_10 * D46_tmp_s) + D46_tmp_11 * D46_tmp_s) + D46_tmp_tmp_e *
                        D46_tmp_tmp_7) + D46_tmp_12 * D46_tmp_tmp_6) + tmp_25 *
                      tmp_a) + D46_tmp_12 * D56_tmp_tmp_3) +
                    rtP_HexaConstants.Inertia[8] * D46_tmp_tmp_1) +
                   rtP_ArmConstants.Inertia1[0] * D46_tmp_w) -
    rtP_ArmConstants.Inertia1[4] * D46_tmp_w;
  tmp_o = D47_tmp_1 * D46_tmp_w;
  tmp_p = -D46_tmp_h;
  tmp_28 = D47_tmp_tmp_tmp * t_a;
  tmp_4f = D47_tmp_tmp_tmp * u_a;
  tmp_6x = D47_tmp_tmp_tmp * x_a;
  tmp_6y = D47_tmp_tmp_tmp * y_a;
  tmp_6z = D67_tmp * o_a;
  tmp_70 = D67_tmp_0 * o_a;
  tmp_71 = D48_tmp * s_a + tmp_28;
  tmp_72 = D48_tmp * w_a;
  D46_tmp_tmp_b = ((((((((((D46_tmp_tmp_b + D56_tmp_tmp) + D56_tmp_tmp_9) +
    D56_tmp_tmp_6) + D56_tmp_tmp_0) + tmp_28) + D56_tmp_tmp_8) + tmp_4f) + tmp_z)
                    - tmp_10) + tmp_11) + tmp_12;
  tmp_73 = D67_tmp * p_a;
  tmp_74 = D67_tmp_0 * p_a;
  tmp_75 = (((((tmp_71 + D56_tmp_tmp_8) + tmp_4f) + D48_tmp * v_a) - tmp_10) +
            tmp_11) + tmp_12;
  tmp_76 = D48_tmp * ab_a;
  tmp_hr[44] = -(((((((((((((((((((((((((((((((((((((((((((((D46_tmp_tmp_1 -
    tmp_o) - D47_tmp_2 * D46_tmp_w) + rtP_ArmConstants.Inertia2[0] * tmp) -
    rtP_ArmConstants.Inertia2[4] * tmp) + tmp_p * rtP_ArmConstants.Mass2 * tmp)
    + -2.0 * rtP_ArmConstants.Inertia1[0] * D46_tmp_y) + -2.0 *
    rtP_ArmConstants.Inertia1[4] * D46_tmp_y) + 4.0 * rtP_ArmConstants.Inertia1
    [8] * D46_tmp_y) + -2.0 * rtP_ArmConstants.Inertia2[0] * D46_tmp_y) + -2.0 *
    rtP_ArmConstants.Inertia2[4] * D46_tmp_y) + 4.0 * rtP_ArmConstants.Inertia2
    [8] * D46_tmp_y) + 4.0 * rtP_HexaConstants.Inertia[0] * D46_tmp_y) + -2.0 *
    rtP_HexaConstants.Inertia[4] * D46_tmp_y) + -2.0 *
    rtP_HexaConstants.Inertia[8] * D46_tmp_y) + tmp_15 * D46_tmp_y) + tmp_1r *
    D46_tmp_y) + tmp_16 * D46_tmp_y) + ginv_tmp_tmp * D46_tmp_y) + tmp_17 *
    D46_tmp_y) + rtP_HexaConstants.Inertia[4] * tmp_0) + D56_tmp_h * tmp_0) +
    D56_tmp_i * tmp_0) + rtP_HexaConstants.Inertia[4] * tmp_2) -
    rtP_HexaConstants.Inertia[8] * tmp_2) + D56_tmp_h * tmp_2) + D56_tmp_i *
    tmp_2) - rtP_ArmConstants.Inertia1[0] * tmp_4) + rtP_ArmConstants.Inertia1[4]
    * tmp_4) + D47_tmp_1 * tmp_4) + D47_tmp_2 * tmp_4) -
    rtP_ArmConstants.Inertia2[0] * tmp_6) + rtP_ArmConstants.Inertia2[4] * tmp_6)
    + D47_tmp * tmp_6) + D46_tmp_k * D46_tmp_tmp_2) + D46_tmp_l * D46_tmp_tmp_2)
    + tmp_q * tmp_e) + D46_tmp_j * D46_tmp_tmp_8) + D46_tmp_m * smax_tmp) +
                       tmp_25 * D15_tmp_tmp_0) + D46_tmp_k * tmp_7) + D46_tmp_l *
                     tmp_7) + D46_tmp_m * tmp_1) + D46_tmp_j * tmp_3) * (-0.5 *
    rtu_InBus1_Velocities[5]) + ((((((((((((((((((((((((((((((((((((((tmp_13 *
    tmp_9s + D56_tmp_tmp_7) + tmp_14 * tmp_9t) + tmp_y * tmp_9u) + tmp_15 *
    tmp_9v) + tmp_1r * tmp_9w) + tmp_16 * tmp_9x) + ginv_tmp_tmp * tmp_9y) +
    tmp_17 * tmp_9z) + tmp_1s) - tmp_1t) + tmp_1u) + tmp_1v) + tmp_1w) + tmp_1x)
    + tmp_18) + tmp_1y) + tmp_1z) - tmp_19) + tmp_1a) + tmp_1b) + tmp_1c) +
    tmp_1d) + tmp_20) + tmp_1e) + tmp_21) + tmp_1f) - tmp_1g) + tmp_1h) + tmp_1i)
    + tmp_1j) + tmp_1k) + tmp_1l) + tmp_1m) + tmp_1n) + tmp_1o) + tmp_1p) +
    tmp_1q) * rtu_InBus1_Velocities[3] + (((((((((((((((((((((((((((((((tmp_13 *
    tmp_9n + D46_tmp_tmp_b) + tmp_14 * tmp_9o) + tmp_15 * tmp_9p) + tmp_16 *
    tmp_9q) + tmp_17 * tmp_9r) + tmp_6z) + tmp_70) + tmp_18) + tmp_73) + tmp_74)
    - tmp_19) + tmp_1a) + tmp_1b) + tmp_1c) + tmp_1d) + tmp_6x) + tmp_1e) +
    tmp_6y) + tmp_1f) - tmp_1g) + tmp_1h) + tmp_1i) + tmp_1j) + tmp_1k) + tmp_1l)
    + tmp_1m) + tmp_1n) + tmp_1o) + tmp_1p) + tmp_1q) * rtu_InBus1_Velocities[6]
    + ((((((((((((((tmp_14 * tmp_9l + tmp_75) + tmp_16 * tmp_9m) + tmp_72) +
                 tmp_6x) + tmp_1e) + tmp_6y) + tmp_76) - tmp_1g) + tmp_1h) +
           tmp_1i) + tmp_1l) + tmp_1m) + tmp_1p) + tmp_1q) *
    rtu_InBus1_Velocities[7]))) * 0.25);
  D46_tmp_w = rtP_ArmConstants.MC1 * rtu_InBus1_Velocities[5];
  D46_tmp_w = D46_tmp_w * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  tmp_0 = rtu_InBus1_Velocities[5] * rtP_ArmConstants.Hexa_to_joint_L;
  tmp_0 *= rtP_ArmConstants.l1_dim;
  tmp_0 *= rtP_ArmConstants.Mass2;
  tmp_2 = rtP_ArmConstants.MC2 * rtu_InBus1_Velocities[5];
  tmp_6 = tmp_2 * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2;
  D46_tmp_tmp_1 = tmp_6 * t_a;
  D56_tmp_tmp_7 = tmp_6 * u_a;
  ginv_tmp_tmp = (((((((((((((((((((D46_tmp_w * r_a + tmp_60) + tmp_0 * r_a) +
    tmp_61) + D46_tmp_w * m_a) + tmp_0 * m_a) - tmp_62) + tmp_63) + tmp_64) +
    tmp_65) + tmp_66) + D46_tmp_tmp_1) + tmp_67) + D56_tmp_tmp_7) + tmp_68) -
                      tmp_69) + tmp_6a) + tmp_6b) + tmp_6c * tmp_a0) + tmp_6d *
                  tmp_a1) + tmp_6e * tmp_a2;
  tmp_o = tmp_6f * tmp_a3;
  tmp_hw = _mm_mul_pd(_mm_set_pd(rtP_ArmConstants.MC1, -2.0), _mm_set1_pd
                      (rtu_InBus1_Velocities[5]));
  _mm_storeu_pd(&tmp_hv[0], tmp_hw);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  tmp_p = tmp_hv[0];
  tmp_q = tmp_hv[1];
  tmp_y = rtP_ArmConstants.Hexa_to_joint_L;
  tmp_1r = D46_tmp_z * rtu_InBus1_Velocities[4] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1;
  tmp_1s = tmp_24 * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  tmp_1t = D46_tmp_f * rtu_InBus1_Velocities[4];
  tmp_1u = tmp_1t * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2;
  tmp_1v = tmp_6 * x_a;
  tmp_1w = tmp_6 * y_a;
  tmp_1x = tmp_1u * smax;
  tmp_1y = tmp_1u * D46_tmp_n;
  tmp_hr[52] = -(((((((((((((((((((((((((((((((((((((((((((((((ginv_tmp_tmp +
    tmp_o) + tmp_6g * tmp_a4) + D46_tmp_w * o_a) + tmp_0 * o_a) + tmp_p *
    rtP_ArmConstants.Inertia1[7] * D46_tmp_3) + tmp_q * tmp_y *
    rtP_ArmConstants.Mass1 * p_a) + tmp_0 * p_a) - tmp_4h) + tmp_4i) + tmp_4j) +
    tmp_6i) + tmp_6j) + tmp_1v) + tmp_6k) + tmp_1w) + tmp_6l) - tmp_4l) + tmp_4m)
    + tmp_4n) + tmp_1r * tmp_a5) + tmp_1s * tmp_a6) + tmp_6m) + tmp_6n) + tmp_2h)
    + tmp_2i) + tmp_2j) + tmp_2k) + tmp_1r * l_a) + tmp_1s * l_a) + tmp_1x) +
    tmp_6o) + tmp_6p) + tmp_6q) + tmp_3b) + tmp_3d) + tmp_3e) + tmp_1y) + tmp_2b)
    + tmp_6r) + tmp_6s) + tmp_6t) + tmp_6u) + tmp_6v) + tmp_2g) + tmp_6w) +
                  tmp_2l) * 0.25);
  tmp_2 = tmp_2 * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  ginv_tmp_tmp = tmp_1t * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  tmp_hr[60] = -((((((((((((((((((((((((((((((((((ginv_tmp_tmp_0 * 4.0 *
    rtP_ArmConstants.Inertia2[6] * D15_tmp_0 + tmp_5v) + tmp_2 * s_a) +
    D46_tmp_tmp_1) + tmp_67) + D56_tmp_tmp_7) + tmp_2 * v_a) - tmp_69) + tmp_6a)
    + tmp_6b) + tmp_6d * tmp_a7) + tmp_6f * tmp_a8) + tmp_2 * w_a) + tmp_1v) +
    tmp_6k) + tmp_1w) + tmp_2 * ab_a) - tmp_4l) + tmp_4m) + tmp_4n) +
    ginv_tmp_tmp * tmp_a9) + tmp_1x) + tmp_6o) + tmp_6p) + tmp_6q) + tmp_3b) +
    tmp_3d) + tmp_3e) + tmp_1y) + ginv_tmp_tmp * D46_tmp_q) + tmp_6t) + tmp_6u)
                   + tmp_6w) + tmp_2l) * 0.25);
  D46_tmp_tmp_1 = rtP_ArmConstants.Inertia2[7] * D46_tmp_2;
  D56_tmp_tmp_7 = rtP_ArmConstants.Inertia2[7] * D46_tmp_4;
  tmp_o = rtP_ArmConstants.Inertia2[6] * D46_tmp_6;
  tmp_p = rtP_ArmConstants.Inertia2[6] * D46_tmp_8;
  tmp_q = D56_tmp_g * D46_tmp_r;
  tmp_y = D46_tmp_tmp_e * D46_tmp_tmp_4;
  tmp_1t = D56_tmp_f * D46_tmp_p;
  tmp_1v = rtP_ArmConstants.Inertia2[0] * D56_tmp_6;
  tmp_1w = (tmp_71 + D46_tmp_tmp_1) - tmp_72;
  D46_tmp_tmp_1 = (((((((((((rtP_ArmConstants.Inertia1[7] * D46_tmp_1 + tmp_n) +
    tmp_28) + D46_tmp_tmp_1) - tmp_6z) - tmp_70) + rtP_ArmConstants.Inertia1[7] *
                        D46_tmp_3) - tmp_6x) + D56_tmp_tmp_7) +
                     rtP_ArmConstants.Inertia1[6] * D46_tmp_5) + tmp_o) +
                   rtP_ArmConstants.Inertia1[6] * D46_tmp_7) + tmp_p;
  tmp_hr[29] = -(((((((((((((((((((((D47_tmp_3 - D56_tmp_tmp_4 * D46_tmp_9) +
    ginv_tmp_0 * tmp_ab) + rtP_ArmConstants.Inertia1[0] * D46_tmp_a) -
    ginv_tmp_6) - ginv_tmp_7) - ginv_tmp_8) + D46_tmp_10 * D46_tmp_b) +
    D46_tmp_11 * D46_tmp_b) + D46_tmp_j * tmp_ac) + ginv_tmp_1) + ginv_tmp_9) -
    ginv_tmp_a) - ginv_tmp_b) + D46_tmp_12 * D46_tmp_t) + tmp_y) + tmp_1t) +
                     tmp_q) * tmp_24 + D45_tmp_1 * tmp_5w) + (((D56_tmp - tmp_1v)
    + D56_tmp_r) + D56_tmp_s) * rtu_InBus1_Velocities[5]) * tmp_aa +
                  (((((-rtP_ArmConstants.MC2 * rtP_ArmConstants.Hexa_to_joint_L *
                       rtP_ArmConstants.Mass2 * x_a + tmp_1w) + D56_tmp_tmp_7) +
                     tmp_o) + tmp_p) * tmp_29 + D46_tmp_tmp_1 * tmp_i2)) * 0.25);
  D56_tmp_tmp_4 = 2.0 * rtu_InBus1_Velocities[3];
  tmp_n = D56_tmp_tmp_4 * D46_tmp_tmp_3;
  tmp_1x = D56_tmp_tmp_4 * rtP_HexaConstants.Inertia[4];
  tmp_1y = tmp_i * rtP_HexaConstants.Inertia[8];
  tmp_1z = tmp_n * rtP_ArmConstants.Mass1;
  tmp_n *= rtP_ArmConstants.Mass2;
  tmp_20 = tmp_27 * rtu_InBus1_Velocities[3] * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  tmp_21 = tmp_4g * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  tmp_25 = tmp_j * rtP_ArmConstants.Inertia1[6];
  tmp_27 = tmp_j * rtP_ArmConstants.Inertia2[6];
  tmp_29 = tmp_20 * r_a;
  tmp_2b = tmp_21 * r_a;
  tmp_2g = (((((((((((tmp_25 * tmp_9 + tmp_27 * tmp_b) + tmp_1x * q_a) + tmp_2o)
                   + tmp_1y * q_a) + tmp_2p) + tmp_1z * q_a) + tmp_2q) + tmp_n *
               q_a) + tmp_2r) + tmp_29) + tmp_2b) + tmp_2t;
  tmp_2h = 4.0 * rtP_ArmConstants.MC1;
  tmp_2i = tmp_2h * rtu_InBus1_Velocities[3] * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  tmp_2j = tmp_5w * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim;
  tmp_2k = rtP_ArmConstants.Mass2;
  tmp_2a *= rtu_InBus1_Velocities[3];
  tmp_2l = 4.0 * rtP_ArmConstants.MC2;
  tmp_2o = tmp_2l * rtu_InBus1_Velocities[3];
  tmp_2p = tmp_4g * D46_tmp_tmp_3;
  tmp_2q = tmp_i0 * D46_tmp_tmp_3;
  tmp_2r = tmp_f * rtu_InBus1_Velocities[3] * rtP_ArmConstants.Mass1;
  tmp_2t = D56_tmp_tmp_4 * D46_tmp_i * rtP_ArmConstants.Mass2;
  tmp_3b = tmp_2a * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  tmp_2a = tmp_2a * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2;
  tmp_3d = tmp_2o * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2;
  tmp_2o = tmp_2o * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  tmp_3e = tmp_i * rtP_ArmConstants.Inertia2[0];
  tmp_4h = D56_tmp_tmp_4 * rtP_ArmConstants.Inertia2[4];
  tmp_4i = tmp_m * rtu_InBus1_Velocities[3] * rtP_ArmConstants.Mass2;
  tmp_2j *= tmp_2k;
  tmp_2k = D56_tmp_tmp_5 * rtP_ArmConstants.Inertia1[3];
  tmp_20 *= o_a;
  tmp_21 *= o_a;
  tmp_d *= tmp_2k;
  tmp_4j = tmp_2a * t_a;
  tmp_4l = tmp_3b * s_a;
  D56_tmp_tmp_4 = ((((((((((((((((((((((((((((((((((((((((((((((((tmp_2g +
    tmp_2u) + tmp_2i * m_a) + tmp_2v) + tmp_2j * m_a) + tmp_2w) + tmp_i *
    rtP_ArmConstants.Inertia1[0] * D56_tmp_7) + tmp_2x) + D56_tmp_tmp_4 *
    rtP_ArmConstants.Inertia1[4] * D56_tmp_7) + tmp_2y) + tmp_2r * D56_tmp_7) +
    tmp_2z) + tmp_2t * D56_tmp_7) + tmp_30) + tmp_4l) + tmp_4j) + tmp_32) +
    tmp_33) + tmp_3d * u_a) + tmp_34) + tmp_2o * v_a) + tmp_3a) + tmp_3e *
    D56_tmp_8) + tmp_3c) + tmp_4h * D56_tmp_8) + tmp_3n) + tmp_4i * D56_tmp_8) +
    tmp_3o) + tmp_4g * rtP_ArmConstants.Inertia1[8] * tmp_ad) + tmp_4g *
    rtP_ArmConstants.Inertia2[8] * tmp_ae) + tmp_4g * rtP_HexaConstants.Inertia
    [0] * tmp_af) + tmp_3h * rtu_InBus1_Velocities[3] * rtP_ArmConstants.Mass1 *
    tmp_ag) + tmp_2p * rtP_ArmConstants.Mass1 * tmp_ah) + tmp_3p *
    rtu_InBus1_Velocities[3] * rtP_ArmConstants.Mass2 * tmp_ai) + tmp_2p *
    rtP_ArmConstants.Mass2 * tmp_aj) + tmp_4g * D46_tmp_i *
    rtP_ArmConstants.Mass2 * tmp_ak) + tmp_1x * n_a) + tmp_i0 *
    rtP_HexaConstants.Inertia[4] * n_a) + tmp_1y * n_a) + tmp_24 *
    rtP_HexaConstants.Inertia[8] * n_a) + tmp_1z * n_a) + tmp_2q *
    rtP_ArmConstants.Mass1 * n_a) + tmp_n * n_a) + tmp_2q *
                        rtP_ArmConstants.Mass2 * n_a) + tmp_20) + tmp_21) +
                     tmp_2s * D46_tmp_3) + tmp_d) + tmp_2i * p_a) + tmp_2h *
    rtu_InBus1_Velocities[4] * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1 * p_a;
  tmp_hw = _mm_set1_pd(rtP_ArmConstants.Hexa_to_joint_L);
  tmp_i3 = _mm_set1_pd(rtP_ArmConstants.Mass2);
  tmp_hx = _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd
    (4.0), _mm_loadu_pd(&rtu_InBus1_Velocities[3])), tmp_hw), _mm_set1_pd
    (rtP_ArmConstants.l1_dim)), tmp_i3), _mm_set1_pd(p_a));
  _mm_storeu_pd(&tmp_hv[0], tmp_hx);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  tmp_i = tmp_hv[0];
  tmp_n = tmp_hv[1];
  tmp_hx = _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(-2.0), _mm_loadu_pd
    (&rtu_InBus1_Velocities[3])), _mm_set1_pd(rtP_ArmConstants.Inertia1[0]));
  _mm_storeu_pd(&tmp_hv[0], tmp_hx);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  tmp_1x = tmp_hv[0];
  tmp_1y = tmp_hv[1];
  tmp_hx = _mm_set1_pd(2.0);
  tmp_hy = _mm_mul_pd(tmp_hx, _mm_loadu_pd(&rtu_InBus1_Velocities[3]));
  _mm_storeu_pd(&tmp_hv[0], tmp_hy);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  tmp_1z = tmp_hv[0];
  tmp_2g = tmp_hv[1];
  tmp_2p = tmp_2l * rtu_InBus1_Velocities[4];
  tmp_2q = D47_tmp_tmp_tmp * D46_tmp_t;
  tmp_2s = tmp_5w * rtP_ArmConstants.Inertia1[3];
  tmp_2v = tmp_3q * rtP_ArmConstants.Inertia1[7];
  tmp_2w = tmp_3q * rtP_ArmConstants.Inertia2[7];
  tmp_2x = rtP_ArmConstants.Inertia1[0] - rtP_ArmConstants.Inertia1[4];
  tmp_f = tmp_f * rtu_InBus1_Velocities[4] * rtP_ArmConstants.Mass1;
  tmp_2y = tmp_i0 * D46_tmp_i * rtP_ArmConstants.Mass2;
  tmp_2z = tmp_24 * rtP_ArmConstants.Inertia2[0];
  tmp_30 = tmp_i0 * rtP_ArmConstants.Inertia2[4];
  tmp_m = tmp_m * rtu_InBus1_Velocities[4] * rtP_ArmConstants.Mass2;
  tmp_32 = tmp_f * D56_tmp_9;
  tmp_34 = tmp_2y * D56_tmp_9;
  tmp_2a *= x_a;
  tmp_3a = D56_tmp_tmp_5 * rtP_ArmConstants.Inertia2[3];
  tmp_5 *= tmp_3a;
  tmp_3c = tmp_2p * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * ab_a;
  tmp_3h = tmp_2z * D56_tmp_a;
  tmp_3n = tmp_30 * D56_tmp_a;
  tmp_3o = tmp_m * D56_tmp_a;
  tmp_3b *= w_a;
  D56_tmp_tmp_4 = (((((((((((((((((((((((((((((((((((((((((((((((((D56_tmp_tmp_4
    + tmp_i) + tmp_n) + tmp_1x * D56_tmp_9) + tmp_1y * D56_tmp_9) + tmp_1z *
    rtP_ArmConstants.Inertia1[4] * D56_tmp_9) + tmp_2g *
    rtP_ArmConstants.Inertia1[4] * D56_tmp_9) + tmp_2r * D56_tmp_9) + tmp_32) +
    tmp_2t * D56_tmp_9) + tmp_34) + tmp_3b) + tmp_2a) + tmp_31 * D46_tmp_4) +
    tmp_5) + tmp_3d * y_a) + tmp_2p * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2 * y_a) + tmp_2o * ab_a) + tmp_3c) + tmp_3e *
    D56_tmp_a) + tmp_3h) + tmp_4h * D56_tmp_a) + tmp_3n) + tmp_4i * D56_tmp_a) +
    tmp_3o) + tmp_25 * D15_tmp_tmp) + tmp_27 * D46_tmp_tmp) + ((((((((D48_tmp *
    tmp_am + D48_tmp_0) + D47_tmp_0) + ginv_tmp_9) - ginv_tmp_a) - ginv_tmp_b) -
    tmp_2q) - D48_tmp * D46_tmp_tmp_4) + tmp_q) * (tmp_l * tmp_al)) +
    ((((((((((((((tmp_2x - D47_tmp_1) - D47_tmp_2) * D46_tmp_a + (D47_tmp_5 *
    tmp_ao + D47_tmp_4)) + tmp_2c * D46_tmp_b) - D67_tmp_0 * D46_tmp_b) +
    D46_tmp_j * tmp_ap) + D47_tmp_0) + ginv_tmp_9) - ginv_tmp_a) - ginv_tmp_b) -
    tmp_2q) + tmp_y) + tmp_1t) + tmp_q) * (tmp_k * tmp_an)) + tmp_4t) + tmp_4a *
    D46_tmp_tmp_0) + tmp_4b * D46_tmp_tmp_0) + tmp_2v * tmp_8) + tmp_4u) +
    tmp_4v) + tmp_3k * D46_tmp_tmp_7) + tmp_3i * D46_tmp_tmp_6) + tmp_2w * tmp_a)
    + tmp_4w) + tmp_4x) + tmp_4z) + tmp_50) - tmp_51) - tmp_52) - tmp_53) +
                       tmp_2s * D56_tmp_1) + tmp_54) + tmp_56) + tmp_57) -
                   tmp_58) - tmp_59;
  tmp_i = tmp_5w * rtP_ArmConstants.Inertia2[3];
  tmp_k = tmp_i * D56_tmp_2;
  tmp_l = D56_tmp_tmp_5 * rtP_ArmConstants.Inertia1[0];
  tmp_n = D56_tmp_tmp_5 * rtP_ArmConstants.Inertia2[0];
  tmp_q = tmp_4q * tmp_4;
  tmp_y = tmp_3j * D56_tmp_5;
  tmp_1t = tmp_5u * D56_tmp_6;
  tmp_1x = tmp_h * tmp_3;
  tmp_hr[37] = -(((((((((((((((((((((((((((((((((((((((((((((((D56_tmp_tmp_4 +
    tmp_k) + tmp_5a) + tmp_l * D46_tmp_y) + tmp_3r * D46_tmp_y) + tmp_j *
    rtP_ArmConstants.Inertia1[8] * D46_tmp_y) + tmp_n * D46_tmp_y) + tmp_3s *
    D46_tmp_y) + tmp_j * rtP_ArmConstants.Inertia2[8] * D46_tmp_y) + tmp_j *
    rtP_HexaConstants.Inertia[0] * D46_tmp_y) + tmp_3t * D46_tmp_y) +
    D56_tmp_tmp_5 * rtP_HexaConstants.Inertia[8] * D46_tmp_y) + tmp_6e *
    D46_tmp_y) + tmp_6h * D46_tmp_y) + tmp_6f * D46_tmp_y) + tmp_4o * D46_tmp_y)
    + tmp_6g * D46_tmp_y) + tmp_5b) + tmp_5c) + tmp_5d) + tmp_5e) - tmp_5f) +
    tmp_5g) + tmp_5h) + tmp_4y * D46_tmp_7) - tmp_5i) + tmp_5j) + tmp_5k) +
    tmp_q) + tmp_2s * D56_tmp_5) + tmp_y) + tmp_55 * D46_tmp_8) - tmp_5l) +
    tmp_5m) + tmp_5n) + tmp_i * D56_tmp_6) + tmp_1t) + tmp_g * D46_tmp_tmp_2) +
    tmp_3g * D46_tmp_tmp_2) + tmp_2v * tmp_e) + tmp_h * D46_tmp_tmp_8) + tmp_4k *
                       smax_tmp) + tmp_2w * D15_tmp_tmp_0) + tmp_g * tmp_7) +
                    tmp_3g * tmp_7) + tmp_4k * tmp_1) + tmp_1x) * 0.125);
  tmp_hx = _mm_mul_pd(tmp_hx, _mm_set_pd(rtP_ArmConstants.Inertia1[3],
    rtP_ArmConstants.Inertia1[6]));
  _mm_storeu_pd(&tmp_hv[0], tmp_hx);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  D56_tmp_tmp_4 = tmp_hv[0];
  D56_tmp_tmp_5 = tmp_hv[1];
  tmp_i = -2.0 * D46_tmp_tmp_9;
  tmp_j = rtP_ArmConstants.MC1 * D15_tmp;
  tmp_k = -2.0 * rtP_ArmConstants.Mass1;
  tmp_1y = -2.0 * rtP_ArmConstants.Mass2;
  tmp_1z = rtP_ArmConstants.l1_dim * a;
  tmp_25 = rtP_ArmConstants.MC2 * D34_tmp;
  tmp_27 = 4.0 * rtP_ArmConstants.Mass2;
  tmp_2c = ginv_tmp_5 * D56_tmp_tmp_tmp + tmp_2x * D46_tmp;
  tmp_2g = ginv_tmp_tmp_2 + ginv_tmp_tmp_3;
  tmp_2p = ginv_tmp_tmp_1 * 2.0 * D46_tmp_u + 4.0 * rtP_ArmConstants.Inertia2[3]
    * D46_tmp_0;
  tmp_2q = ginv_tmp_4 * 2.0 * D46_tmp_u + -4.0 * rtP_ArmConstants.Inertia2[3] *
    D46_tmp_0;
  tmp_2r = rtP_ArmConstants.MC1 * a;
  tmp_hr[45] = -((((((((((((((((((((((2.0 * tmp_aq * D46_tmp_tmp_9 *
    (rtP_ArmConstants.Inertia1[6] * tmp_ar - rtP_ArmConstants.Inertia1[7] *
    tmp_as) + (rtP_ArmConstants.Inertia1[7] * tmp_au +
    rtP_ArmConstants.Inertia1[6] * tmp_av) * (tmp_i * tmp_at)) + 2.0 * tmp_aw *
    D46_tmp_tmp_9 * ginv_tmp_c) + tmp_i * tmp_ax * ginv_tmp_d) + (tmp_2x *
    tmp_b1 * tmp_b2 + rtP_ArmConstants.Inertia1[3] * D56_tmp_tmp_tmp) * (4.0 *
    tmp_ay * tmp_az * tmp_b0) * tmp_b3) + ((D56_tmp_f * tmp_b5 * tmp_b6 + D25 *
    D25 * rtP_ArmConstants.Inertia1[0]) + D14_tmp_tmp * D14_tmp_tmp *
    rtP_ArmConstants.Inertia1[4]) * (D24 * D24 * -2.0 * tmp_b4) * tmp_b7) +
    ((D28 * D28 * rtP_ArmConstants.Inertia1[4] + D34 * D34 *
      rtP_ArmConstants.Inertia1[0]) + ginv_tmp_e) * (-2.0 * tmp_b8 * (D27 * D27))
    * tmp_b9) - D35 * D35 * tmp_ba * ginv_tmp_f * tmp_bb) - D37 * D37 * tmp_bc *
    ginv_tmp_2 * tmp_bd) + 2.0 * tmp_be * tmp_bf * tmp_bg * (ginv_tmp_3 *
    D46_tmp_0 + ginv_tmp_tmp_1 * D46_tmp_u) * tmp_bh) +
    (rtP_ArmConstants.Hexa_to_joint_L * tmp_bi + tmp_j) * tmp_k * tmp_bj *
    tmp_bk * ((rtP_ArmConstants.Hexa_to_joint_L * tmp_bm + tmp_2r) * tmp_bl -
              (rtP_ArmConstants.Hexa_to_joint_L * tmp_bn + tmp_j) * tmp_bo *
              tmp_bp)) + ((rtP_ArmConstants.Hexa_to_joint_L * tmp_bq + D24_tmp)
    + D24_tmp_0) * tmp_1y * tmp_br * tmp_bs *
    (((rtP_ArmConstants.Hexa_to_joint_L * tmp_bu + tmp_1z) + tmp_25) * tmp_bt -
     ((rtP_ArmConstants.Hexa_to_joint_L * tmp_bv + D24_tmp) + D24_tmp_0) *
     tmp_bw * tmp_bx)) + ((tmp_c4 * tmp_c5 * tmp_c6 + tmp_c2 * tmp_c3) *
    -(rtP_ArmConstants.MC1 * tmp_c1 + rtP_ArmConstants.Hexa_to_joint_L) +
    (tmp_ca * tmp_cb * tmp_cc + -tmp_c8 * tmp_c9) * (rtP_ArmConstants.MC1 *
    tmp_c7)) * ((rtP_ArmConstants.Hexa_to_joint_L * tmp_bz + tmp_j) * (tmp_k *
    tmp_by) * tmp_c0)) + ((rtP_ArmConstants.Hexa_to_joint_L * tmp_ce + D24_tmp)
    + D24_tmp_0) * (tmp_1y * tmp_cd) * tmp_cf * (-((rtP_ArmConstants.l1_dim *
    tmp_cg + rtP_ArmConstants.Hexa_to_joint_L) + D17_tmp_0) * (tmp_cj * tmp_ck *
    tmp_cl + tmp_ch * tmp_ci) + (tmp_cp * tmp_cq * tmp_cr + -tmp_cn * tmp_co) *
    (rtP_ArmConstants.l1_dim * tmp_cm + D17_tmp))) + rtP_ArmConstants.Inertia1[8]
    * D46_tmp_y) + rtP_ArmConstants.Inertia2[8] * D46_tmp_y) +
                       rtP_HexaConstants.Inertia[0] * D46_tmp_y) - D38 * D38 *
                      rtP_HexaConstants.Inertia[8] * D46_tmp_y) - D45 * D45 *
                     rtP_HexaConstants.Inertia[4] * D46_tmp_y) * tmp_i0 +
                    ((((((tmp_cw * tmp_cx * tmp_cy + tmp_cu * tmp_cv) * D17_tmp
    + (tmp_d1 * tmp_d2 * tmp_d3 + -tmp_cz * tmp_d0) * D17_tmp_0) * tmp_27 *
                        (-((rtP_ArmConstants.l1_dim * tmp_d4 +
    rtP_ArmConstants.Hexa_to_joint_L) + D17_tmp_0) * (tmp_d7 * tmp_d8 * tmp_d9 +
    tmp_d5 * tmp_d6) + (tmp_dd * tmp_de * tmp_df + -tmp_db * tmp_dc) *
    (rtP_ArmConstants.l1_dim * tmp_da + D17_tmp)) + ((4.0 * tmp_cs * (D46_tmp_e *
    D46_tmp_e) * tmp_ct * tmp_2g + D47 * D47 * (D48 * D48) * tmp_2p) + D56 * D56
    * (D57 * D57) * tmp_2q)) + (((rtP_ArmConstants.Hexa_to_joint_L * tmp_dh +
    tmp_1z) + tmp_25) * tmp_dg - ((rtP_ArmConstants.Hexa_to_joint_L * tmp_di +
    D24_tmp) + D24_tmp_0) * tmp_dj * tmp_dk) * tmp_27 * ((tmp_dn * tmp_do *
    tmp_dp + -tmp_dl * tmp_dm) * D17_tmp + (tmp_ds * tmp_dt * tmp_du + tmp_dq *
    tmp_dr) * D17_tmp_0)) + -2.0 * tmp_dv * ginv_tmp_c * D46_tmp_y) + -2.0 *
                     tmp_dw * ginv_tmp_d * D46_tmp_y) * rtu_InBus1_Velocities[7])
                   + (((((((((((((D45_tmp * D45_tmp * -2.0 * k_a * (tmp_2x *
    D56_tmp_tmp_tmp + D56_tmp_f * D46_tmp) + D45_tmp_0 * D45_tmp_0 * -2.0 * (c_a
    * c_a) * tmp_2c) + d_a * d_a * 2.0 * (e_a * e_a) * tmp_2c) + 4.0 * tmp_dx *
    (f_a * f_a) * tmp_dy * tmp_2g) + g_a * g_a * (h_a * h_a) * tmp_2p) + i_a *
    i_a * (j_a * j_a) * tmp_2q) + ((tmp_e2 * tmp_e3 * tmp_e4 + tmp_e0 * tmp_e1) *
    (rtP_ArmConstants.l1_dim * tmp_dz + D17_tmp) + (tmp_e8 * tmp_e9 * tmp_ea +
    -tmp_e6 * tmp_e7) * (rtP_ArmConstants.l1_dim * tmp_e5 + D17_tmp_0)) * tmp_27
    * (-((rtP_ArmConstants.l1_dim * tmp_eb + rtP_ArmConstants.Hexa_to_joint_L) +
         D17_tmp_0) * (tmp_ee * tmp_ef * tmp_eg + tmp_ec * tmp_ed) + (tmp_ek *
    tmp_el * tmp_em + -tmp_ei * tmp_ej) * (rtP_ArmConstants.l1_dim * tmp_eh +
    D17_tmp))) + (((rtP_ArmConstants.Hexa_to_joint_L * tmp_eo + tmp_1z) + tmp_25)
                  * tmp_en - ((rtP_ArmConstants.Hexa_to_joint_L * tmp_ep +
    D24_tmp) + D24_tmp_0) * tmp_eq * tmp_er) * tmp_27 * ((tmp_et * tmp_eu -
    tmp_ev * tmp_ew * tmp_ex) * -(rtP_ArmConstants.l1_dim * tmp_es + D17_tmp) +
    (tmp_f1 * tmp_f2 * tmp_f3 + tmp_ez * tmp_f0) * (rtP_ArmConstants.l1_dim *
    tmp_ey + D17_tmp_0))) + ((tmp_f7 * tmp_f8 * tmp_f9 + tmp_f5 * tmp_f6) *
    -(rtP_ArmConstants.MC1 * tmp_f4 + rtP_ArmConstants.Hexa_to_joint_L) +
    (tmp_fd * tmp_fe * tmp_ff + -tmp_fb * tmp_fc) * (rtP_ArmConstants.MC1 *
    tmp_fa)) * (tmp_2h * rtP_ArmConstants.Mass1) * ((tmp_fj * tmp_fk * tmp_fl +
    tmp_fh * tmp_fi) * tmp_fg + (tmp_fp * tmp_fq * tmp_fr + -tmp_fn * tmp_fo) *
    tmp_fm)) + (-(rtP_ArmConstants.Hexa_to_joint_L * tmp_fu + tmp_j) * tmp_fv *
                tmp_fw + (rtP_ArmConstants.Hexa_to_joint_L * tmp_ft + tmp_2r) *
                tmp_fs) * (4.0 * rtP_ArmConstants.Mass1) * ((tmp_g0 * tmp_g1 *
    tmp_g2 + -tmp_fy * tmp_fz) * (rtP_ArmConstants.MC1 * tmp_fx) + (tmp_g6 *
    tmp_g7 * tmp_g8 + tmp_g4 * tmp_g5) * (rtP_ArmConstants.MC1 * tmp_g3))) +
    (rtP_ArmConstants.Inertia1[6] * tmp_ga - rtP_ArmConstants.Inertia1[7] *
     tmp_gb) * (-2.0 * tmp_g9) * D46_tmp_y) + (rtP_ArmConstants.Inertia1[7] *
    tmp_gd + rtP_ArmConstants.Inertia1[6] * tmp_ge) * (-2.0 * tmp_gc) *
                        D46_tmp_y) + -2.0 * tmp_gf * ginv_tmp_c * D46_tmp_y) +
                      -2.0 * tmp_gg * ginv_tmp_d * D46_tmp_y) *
                   rtu_InBus1_Velocities[6]) -
                  (((((((((((((((((((((((((((((((((((((((((D56_tmp_tmp_4 *
    D46_tmp_1 + D56_tmp_tmp_5 * D56_tmp_7) + D56_tmp_o * D46_tmp_2) + ginv_tmp_3
    * D56_tmp_8) + D56_tmp_p * D46_tmp_3) + ginv_tmp_5 * D56_tmp_9) + D56_tmp_q *
    D46_tmp_4) + ginv_tmp_3 * D56_tmp_a) - D56_tmp_tmp_a) + D56_tmp_tmp_b) -
    D56_tmp_tmp_c) - D56_tmp_tmp_d) + D56_tmp_l * D46_tmp_5) + D46_tmp_10 *
    D56_tmp_0) + D46_tmp_11 * D56_tmp_0) + D56_tmp_tmp_e) - D56_tmp_tmp_f) -
    D56_tmp_tmp_g) - D56_tmp_tmp_h) + D56_tmp_m * D46_tmp_6) + D46_tmp_12 *
    D56_tmp_b) + D46_tmp_tmp_e * D56_tmp_c) + D56_tmp_tmp_i) - D56_tmp_tmp_j) -
    D56_tmp_tmp_k) - D56_tmp_tmp_l) + D56_tmp_tmp_m) - D56_tmp_tmp_n) +
    -D46_tmp_tmp_3 * rtP_ArmConstants.Mass2 * D56_tmp_3) + D56_tmp_j * D46_tmp_7)
    + D46_tmp_10 * D56_tmp_4) + D46_tmp_11 * D56_tmp_4) + D56_tmp_tmp_o) -
    D56_tmp_tmp_p) - D56_tmp_tmp_q) - D56_tmp_tmp_r) + D56_tmp_k * D46_tmp_8) +
                       D46_tmp_12 * D56_tmp_d) + D46_tmp_tmp_e * D56_tmp_e) +
                     tmp_1v) - D56_tmp_r) - D56_tmp_s) * (rtu_InBus1_Velocities
    [3] * tmp_gh)) * 0.25);
  D46_tmp_tmp_9 = tmp_5w * rtP_ArmConstants.Inertia1[7];
  D56_tmp_tmp_4 = D46_tmp_tmp_f * rtu_InBus1_Velocities[4] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1;
  D56_tmp_tmp_5 = tmp_i0 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  tmp_i = tmp_24 * rtP_ArmConstants.Inertia1[0];
  tmp_j = tmp_i0 * rtP_ArmConstants.Inertia1[4];
  tmp_k = tmp_3q * rtP_ArmConstants.Inertia2[3] * D46_tmp_c;
  tmp_b *= tmp_3m;
  tmp_9 = (((((((((((((tmp_3q * rtP_ArmConstants.Inertia1[3] * D46_tmp_a + tmp_k)
                      + tmp_3l * tmp_9) + tmp_b) + tmp_2i * r_a) + tmp_1r * r_a)
                  + tmp_2j * r_a) + tmp_1s * r_a) + D46_tmp_tmp_9 * D46_tmp_1) +
               tmp_2k * tmp_c) + D56_tmp_tmp_4 * m_a) + D56_tmp_tmp_5 * m_a) +
            tmp_i * D56_tmp_7) + tmp_j * D56_tmp_7) + tmp_f * D56_tmp_7;
  tmp_c = tmp_2y * D56_tmp_7;
  tmp_hx = _mm_set_pd(-2.0, 4.0);
  tmp_hy = _mm_set1_pd(rtP_ArmConstants.MC2);
  tmp_hw = _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_mul_pd(tmp_hx, tmp_hy),
    _mm_loadu_pd(&rtu_InBus1_Velocities[3])), tmp_hw), tmp_i3);
  _mm_storeu_pd(&tmp_hv[0], tmp_hw);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  tmp_f = tmp_hv[0];
  tmp_1v = tmp_hv[1];
  tmp_hw = _mm_mul_pd(tmp_hx, _mm_set_pd(rtu_InBus1_Velocities[5],
    rtu_InBus1_Velocities[3]));
  _mm_storeu_pd(&tmp_hv[0], tmp_hw);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  tmp_1y = tmp_hv[0];
  tmp_1z = tmp_hv[1];
  tmp_hw = _mm_mul_pd(_mm_mul_pd(_mm_set_pd(4.0, 2.0), tmp_hy), _mm_set1_pd
                      (rtu_InBus1_Velocities[4]));
  _mm_storeu_pd(&tmp_hv[0], tmp_hw);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  tmp_25 = tmp_hv[0];
  tmp_27 = tmp_hv[1];
  tmp_2c = tmp_5w * rtP_ArmConstants.Inertia2[7];
  tmp_2g = D46_tmp_d * rtu_InBus1_Velocities[4];
  tmp_2h = tmp_2g * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2;
  tmp_2k = tmp_2z * D56_tmp_8;
  tmp_2p = tmp_30 * D56_tmp_8;
  tmp_m *= D56_tmp_8;
  tmp_2q = tmp_26 * rtP_ArmConstants.Inertia2[8];
  tmp_2r = tmp_1u * x_a;
  tmp_2s = tmp_2c * D46_tmp_4;
  tmp_2t = tmp_2h * y_a;
  D46_tmp_tmp *= tmp_2n;
  tmp_2n = -6.0 * rtP_ArmConstants.MC2 * rtu_InBus1_Velocities[5];
  tmp_2v = tmp_2n * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2 *
    smax;
  tmp_n *= D46_tmp_r;
  tmp_9 = (((((((((((((((((((((((((((((((((((((((((((((((((tmp_9 + tmp_c) +
    tmp_35) + tmp_f * t_a) + tmp_1v * t_a) + tmp_1y * rtP_ArmConstants.Inertia2
    [7] * D46_tmp_2) + tmp_1z * rtP_ArmConstants.Inertia2[3] * D46_tmp_x) +
    tmp_25 * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2 * u_a) +
    tmp_27 * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * v_a) + tmp_2k) +
    tmp_2p) + tmp_m) + tmp_26 * rtP_ArmConstants.Inertia1[8] * tmp_gi) + tmp_2q *
    tmp_gj) + tmp_3u * tmp_gk) + tmp_3v * tmp_gl) + tmp_3w * tmp_gm) + tmp_20) +
    tmp_1r * o_a) + tmp_21) + tmp_1s * o_a) + D46_tmp_tmp_9 * D46_tmp_3) + tmp_d)
    + D56_tmp_tmp_4 * p_a) + D56_tmp_tmp_5 * p_a) + tmp_i * D56_tmp_9) + tmp_j *
    D56_tmp_9) + tmp_32) + tmp_34) + tmp_3x) + tmp_2a) + tmp_2r) + tmp_2s) +
    tmp_5) + tmp_2t) + tmp_3c) + tmp_3h) + tmp_3n) + tmp_3o) + tmp_2m *
                     D15_tmp_tmp) + D46_tmp_tmp) + -6.0 * rtP_ArmConstants.MC1 *
                   rtu_InBus1_Velocities[5] * rtP_ArmConstants.Hexa_to_joint_L *
                   rtP_ArmConstants.Mass1 * tmp_gn) + -6.0 *
                  rtu_InBus1_Velocities[5] * rtP_ArmConstants.Hexa_to_joint_L *
                  rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * tmp_go) +
                 tmp_l * D46_tmp_p) + D56_tmp_tmp_2 * rtP_ArmConstants.Inertia1
                [4] * D46_tmp_p) + tmp_6e * D46_tmp_p) + tmp_6g * D46_tmp_p) +
             tmp_g * l_a) + tmp_3g * l_a) + tmp_2v) + tmp_n;
  tmp_c = D56_tmp_tmp_2 * rtP_ArmConstants.Inertia2[4] * D46_tmp_r;
  tmp_d = tmp_2l * rtu_InBus1_Velocities[5] * rtP_ArmConstants.l1_dim;
  D15_tmp_tmp = rtP_ArmConstants.Mass2;
  D46_tmp_tmp_9 = tmp_5w * rtP_ArmConstants.Inertia1[6];
  D56_tmp_tmp_2 = tmp_6f * D46_tmp_r;
  D56_tmp_tmp_4 = tmp_4k * D46_tmp_n;
  D46_tmp_tmp_6 *= tmp_6;
  tmp_a *= tmp_4r;
  D56_tmp_tmp_3 *= tmp_6;
  D56_tmp_tmp_5 = tmp_5x * D46_tmp_6;
  tmp_f = tmp_5u * D56_tmp_2;
  tmp_g = tmp_5x * D46_tmp_8;
  D56_tmp_tmp_7 = (((tmp_1w - tmp_6x) + D56_tmp_tmp_7) + tmp_o) + tmp_p;
  tmp_i = D56_tmp_tmp_7 * tmp_5y;
  smax_tmp *= tmp_6;
  D15_tmp_tmp_0 *= tmp_4s;
  tmp_6 *= tmp_1;
  tmp_j = D46_tmp_w * D46_tmp_tmp_0;
  D46_tmp_tmp_0 *= tmp_0;
  tmp_l = D46_tmp_w * D46_tmp_s;
  tmp_o = tmp_0 * D46_tmp_s;
  tmp_p = D46_tmp_w * D46_tmp_tmp_2;
  D46_tmp_tmp_2 *= tmp_0;
  D46_tmp_w *= tmp_7;
  tmp_0 *= tmp_7;
  tmp_hr[53] = -(((((((((((((((((((((((((((((((((((((((((((((((tmp_9 + tmp_c) +
    D56_tmp_tmp_2) + D56_tmp_tmp_4) + tmp_d * D15_tmp_tmp * D46_tmp_q) + tmp_h *
    D46_tmp_v) + tmp_j) + D46_tmp_tmp_0) + tmp_4p * tmp_8) + tmp_l) + tmp_o) +
    D46_tmp_tmp_6) + tmp_a) + D56_tmp_tmp_3) + D46_tmp_tmp_9 * D46_tmp_5) -
    tmp_50) + tmp_51) + tmp_52) + tmp_53) + tmp_3j * D56_tmp_1) + D56_tmp_tmp_5)
    + -rtu_InBus1_Velocities[5] * rtP_ArmConstants.Inertia2[0] * tmp) + tmp_58)
    + tmp_59) + tmp_f) + D46_tmp_tmp_9 * D46_tmp_7) + -rtu_InBus1_Velocities[5] *
    rtP_ArmConstants.Inertia1[0] * tmp_4) + tmp_5j) + tmp_5k) + tmp_q) + tmp_y)
    + tmp_g) + tmp_i) + D46_tmp_tmp_1 * tmp_5z) - tmp_5l) + tmp_5m) + tmp_5n) +
    tmp_1t) + tmp_p) + D46_tmp_tmp_2) + tmp_49 * tmp_e) + smax_tmp) +
                      D15_tmp_tmp_0) + D46_tmp_w) + tmp_0) + tmp_6) + tmp_1x) *
                 0.125);
  tmp = tmp_2g * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  D46_tmp_x = (((((((tmp_2o * s_a + (tmp_k + tmp_b)) + ginv_tmp_tmp * s_a) +
                   tmp_3d * t_a) + tmp_1u * t_a) + tmp_2c * D46_tmp_2) + tmp_3a *
                D46_tmp_x) + tmp_2h * u_a) + tmp * v_a;
  D46_tmp_v *= tmp_2;
  tmp_4 = tmp_2 * D46_tmp_tmp_7;
  tmp_7 = tmp_2 * D46_tmp_tmp_8;
  tmp_2 *= tmp_3;
  tmp_hr[61] = -(((((((((((((((((((((((((((((((((((((((((((((((D46_tmp_x +
    tmp_2k) + tmp_2p) + tmp_m) + tmp_2q * tmp_gp) + tmp_3v * tmp_gq) + tmp_3b) +
    ginv_tmp_tmp * w_a) + tmp_2a) + tmp_2r) + tmp_2s) + tmp_5) + tmp_2t) + tmp *
    ab_a) + tmp_3h) + tmp_3n) + tmp_3o) + D46_tmp_tmp) + tmp_2n *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * tmp_gr) + tmp_2v) + tmp_n)
    + tmp_c) + D56_tmp_tmp_2) + D56_tmp_tmp_4) + tmp_h * D46_tmp_q) + D46_tmp_v)
    + tmp_4) + D46_tmp_tmp_6) + tmp_a) + D56_tmp_tmp_3) + D56_tmp_tmp_5) -
    tmp_57) + tmp_58) + tmp_59) + tmp_f) + tmp_g) + D56_tmp_tmp_7 * tmp_5z) +
    tmp_i) - tmp_5l) + tmp_5m) + tmp_5n) + tmp_1t) + tmp_7) + smax_tmp) +
                    D15_tmp_tmp_0) + tmp_6) + tmp_2) * 0.125);
  D46_tmp_x = tmp_39 * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  tmp_hr[30] = -((D14_tmp_0 * tmp_gt + D14_tmp_4) *
                 rtP_ArmConstants.Hexa_to_joint_L * (rtu_InBus1_Velocities[3] -
    rtu_InBus1_Velocities[5] * tmp_gu) + D46_tmp_x * tmp_gs);
  tmp_hr[38] = -((((((((((((((((D67_tmp * tmp_gv + tmp_22) + D67_tmp_0 * tmp_gw)
    - tmp_r) + tmp_s) + tmp_t) + tmp_u) + D67_tmp * l_a) + tmp_2d) + tmp_2e) -
                       tmp_v) + tmp_w) + tmp_x) + tmp_2f) + tmp_23) * tmp_i0 -
                  ((((((((((((((((((((((((((((((tmp_13 * tmp_gx + D46_tmp_tmp_b)
    + tmp_14 * tmp_gy) + tmp_15 * tmp_gz) + tmp_16 * tmp_h0) + tmp_17 * tmp_h1)
    + tmp_6z) + tmp_70) + tmp_18) + tmp_73) + tmp_74) - tmp_19) + tmp_1a) +
    tmp_1b) + tmp_1c) + tmp_1d) + tmp_6x) + tmp_1e) + tmp_6y) + tmp_1f) - tmp_1g)
    + tmp_1h) + tmp_1i) + tmp_1j) + tmp_1k) + tmp_1l) + tmp_1m) + tmp_1n) +
                     tmp_1o) + tmp_1p) + tmp_1q) * rtu_InBus1_Velocities[5]) *
                 0.25);
  tmp = tmp_3d * x_a;
  tmp_3 = (((((((((((((tmp_38 + tmp_29) + tmp_2b) + tmp_2u) + tmp_4j) + tmp_33)
                  + tmp_2i * o_a) + tmp_2j * o_a) + tmp_3y) + tmp) + tmp_3z) +
             tmp_40) + tmp_41) + 6.0 * rtP_ArmConstants.MC1 *
           rtu_InBus1_Velocities[5] * rtP_ArmConstants.Hexa_to_joint_L *
           rtP_ArmConstants.Mass1 * tmp_h2) + 6.0 * rtu_InBus1_Velocities[5] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2 * tmp_h3;
  tmp_5 = 6.0 * rtP_ArmConstants.MC2 * rtu_InBus1_Velocities[5];
  tmp_8 = (((((((-rtP_ArmConstants.Inertia1[0] * D56_tmp_7 + D46_tmp_tmp_a) +
                D56_tmp_tmp) + D56_tmp_tmp_9) + D56_tmp_tmp_6) + D56_tmp_tmp_0)
            + tmp_28) + D56_tmp_tmp_8) + tmp_4f;
  tmp_9 = tmp_5 * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2 *
    smax;
  tmp_a = tmp_3i * D46_tmp_n;
  tmp_hr[46] = -(((((((((((((((((((((((((((((((((((((((((((((((tmp_3 + tmp_42) +
    tmp_45) + tmp_43) + tmp_44) + tmp_4a * l_a) + tmp_4b * l_a) + tmp_9) +
    tmp_46) + tmp_47) + tmp_48) + tmp_a) + tmp_3f) + tmp_4t) - tmp_j) -
    D46_tmp_tmp_0) + tmp_5o) - tmp_l) - tmp_o) - D46_tmp_tmp_6) + tmp_5p) -
    D56_tmp_tmp_3) + tmp_50) - tmp_51) - tmp_52) - tmp_53) + tmp_57) - tmp_58) -
    tmp_59) + tmp_5q * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * tmp_h4
    * tmp_h5) + tmp_5i) - tmp_5j) - tmp_5k) - tmp_q) + tmp_5l) - tmp_5m) -
    tmp_5n) + ((((((((((((((((((((((((((((((((((tmp_8 + tmp_z) - tmp_10) +
    tmp_11) + tmp_12) + tmp_13 * tmp_h6) + tmp_14 * tmp_h7) + tmp_15 * tmp_h8) +
    tmp_16 * tmp_h9) + tmp_17 * tmp_ha) + tmp_6z) + tmp_70) + tmp_18) + tmp_73)
    + tmp_74) - tmp_19) + tmp_1a) + tmp_1b) + tmp_1c) + tmp_1d) + tmp_6x) +
    tmp_1e) + tmp_6y) + tmp_1f) - tmp_1g) + tmp_1h) + tmp_1i) + tmp_1j) + tmp_1k)
                    + tmp_1l) + tmp_1m) + tmp_1n) + tmp_1o) + tmp_1p) + tmp_1q) *
    tmp_24) - tmp_p) - D46_tmp_tmp_2) + tmp_5r) - smax_tmp) + tmp_5s) -
                     D46_tmp_w) - tmp_0) - tmp_6) + tmp_5t) * 0.125);
  tmp_hr[54] = -(D46_tmp_x * tmp_hb);
  tmp_hr[62] = -((ginv_tmp_tmp_0 - rtu_InBus1_Velocities[5] * tmp_hd) *
                 (D46_tmp_o * tmp_hc));
  tmp_hr[31] = -(((rtP_ArmConstants.l1_dim * tmp_hf + tmp_4c) *
                  (rtu_InBus1_Velocities[3] - rtu_InBus1_Velocities[5] * tmp_hg)
                  + rtu_InBus1_Velocities[6] * rtP_ArmConstants.l1_dim * tmp_he)
                 * D14_tmp);
  tmp_hr[39] = -(((((((((((((((tmp_14 * tmp_hi + tmp_75) + tmp_16 * tmp_hj) +
    tmp_72) + tmp_6x) + tmp_1e) + tmp_6y) + tmp_76) - tmp_1g) + tmp_1h) + tmp_1i)
                     + tmp_1l) + tmp_1m) + tmp_1p) + tmp_1q) * (-0.25 *
    rtu_InBus1_Velocities[5]) + (((D47_tmp_tmp_tmp * tmp_hh + tmp_4d) + tmp_4e) *
    rtu_InBus1_Velocities[4] * D34_tmp + -rtu_InBus1_Velocities[4] *
    rtP_ArmConstants.Inertia2[3] * D46_tmp_c));
  tmp_hr[47] = -((((((((((((((((((((((((((((((((((tmp_36 + tmp_37) + tmp_4l) +
    tmp_4j) + tmp_33) + tmp_2o * w_a) + tmp) + tmp_3z) + tmp_41) + tmp_5 *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * tmp_hk) + tmp_9) + tmp_46)
    + tmp_47) + tmp_48) + tmp_a) + tmp_3k * D46_tmp_q) - D46_tmp_v) - tmp_4) -
    D46_tmp_tmp_6) + tmp_5p) - D56_tmp_tmp_3) + tmp_57) - tmp_58) - tmp_59) +
    -8.0 * rtP_ArmConstants.MC2 * rtu_InBus1_Velocities[6] *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * tmp_hl * tmp_hm) + tmp_5l)
    - tmp_5m) - tmp_5n) + ((((((((((((((tmp_14 * tmp_hn + tmp_75) + tmp_16 *
    tmp_ho) + tmp_72) + tmp_6x) + tmp_1e) + tmp_6y) + tmp_76) - tmp_1g) + tmp_1h)
    + tmp_1i) + tmp_1l) + tmp_1m) + tmp_1p) + tmp_1q) * tmp_24) - tmp_7) -
                     smax_tmp) + tmp_5s) + -rtP_ArmConstants.MC2 *
                   rtu_InBus1_Velocities[5] * rtP_ArmConstants.Hexa_to_joint_L *
                   rtP_ArmConstants.Mass2 * tmp_1) - tmp_2) * 0.125);
  tmp_hr[55] = -((D56_tmp_tmp_1 - rtu_InBus1_Velocities[5] * tmp_hq) * (D48_tmp *
    tmp_hp));
  tmp_hr[63] = -0.0;
  D46_tmp_v = std::cos(rtu_InBus1_Positions[4]);
  D46_tmp_w = std::sin(rtu_InBus1_Positions[3]);
  D46_tmp_x = std::cos(rtu_InBus1_Positions[3]);
  tmp = std::sin(rtu_InBus1_Positions[4]);
  tmp_0 = std::cos(rtu_InBus1_Positions[4]);
  tmp_1 = std::cos(rtu_InBus1_Positions[4]);
  std::memset(&tmp_hr[0], 0, 24U * sizeof(real_T));
  std::memset(&tmp_hs[0], 0, sizeof(real_T) << 3U);
  for (ix = 0; ix < 8; ix++) {
    tmp_2 = rtu_InBus1_Velocities[ix];
    for (i = 0; i <= 6; i += 2) {
      tmp_hw = _mm_loadu_pd(&tmp_hr[(ix << 3) + i]);
      tmp_hw = _mm_mul_pd(tmp_hw, _mm_set1_pd(tmp_2));
      tmp_i3 = _mm_loadu_pd(&tmp_hs[i]);
      tmp_hw = _mm_add_pd(tmp_hw, tmp_i3);
      _mm_storeu_pd(&tmp_hs[i], tmp_hw);
    }
  }

  tmp_ht[0] = 0.0;
  tmp_ht[1] = 0.0;
  tmp_ht[2] = ginv_tmp * 9.80665;
  tmp_ht[3] = ((D14_tmp_5 * D46_tmp_w - D34_tmp_0) - D34_tmp_1) * (-9.80665 *
    D46_tmp_v);
  tmp_ht[4] = ((D14_tmp_2 * D46_tmp_x + D15_tmp_1) + D15_tmp_2) * 9.80665 * tmp;
  tmp_ht[5] = 0.0;
  tmp_ht[6] = (-D14_tmp_0 * a - D34_tmp_1) * (-9.80665 * tmp_0);
  tmp_ht[7] = rtP_ArmConstants.MC2 * 9.80665 * rtP_ArmConstants.Mass2 * tmp_1 *
    D34_tmp;
  for (ix = 0; ix <= 6; ix += 2) {
    /* MATLAB Function: '<S1>/MATLAB Function1' */
    tmp_hw = _mm_loadu_pd(&tmp_hs[ix]);
    tmp_i3 = _mm_loadu_pd(&tmp_ht[ix]);
    tmp_hw = _mm_sub_pd(tmp_hw, tmp_i3);
    _mm_storeu_pd(&PD_B.fx[ix], tmp_hw);
  }

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  mldivide_0QKHZcd4(PD_B.ginv, PD_B.fx);

  /* MATLAB Function: '<Root>/GetBInvMatrix' */
  /* :  BM1 = BMatrix(xi); */
  /* 'BMatrix:3' phi = xi(4); */
  /* 'BMatrix:4' th  = xi(5); */
  /* 'BMatrix:5' psi = xi(6); */
  /* 'BMatrix:7' BM=[cos(psi)*cos(th),-cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th), ... */
  /* 'BMatrix:8'     sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th),0,0,0;... */
  /* 'BMatrix:9'     cos(th)*sin(psi), cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th),... */
  /* 'BMatrix:10'     -cos(psi)*sin(phi)+cos(phi)*sin(psi)*sin(th),0,0,0;... */
  /* 'BMatrix:11'     -sin(th),cos(th)*sin(phi),cos(phi)*cos(th),0,0,0;... */
  /* 'BMatrix:12'     0,0,0,1,sin(phi)*tan(th),cos(phi)*tan(th);... */
  /* 'BMatrix:13'     0,0,0,0,cos(phi),-sin(phi);0,0,0,0,sec(th)*sin(phi),cos(phi)*sec(th)]; */
  /* :  BM = blkdiag(BM1, eye(2,2)); */
  D46_tmp_v = std::cos(rtu_InBus1_Positions[5]);
  D46_tmp_w = std::cos(rtu_InBus1_Positions[4]);
  D46_tmp_x = std::cos(rtu_InBus1_Positions[3]);
  tmp = std::sin(rtu_InBus1_Positions[5]);
  tmp_0 = std::cos(rtu_InBus1_Positions[5]);
  tmp_1 = std::sin(rtu_InBus1_Positions[3]);
  tmp_2 = std::sin(rtu_InBus1_Positions[4]);
  tmp_3 = std::sin(rtu_InBus1_Positions[3]);
  tmp_4 = std::sin(rtu_InBus1_Positions[5]);
  tmp_5 = std::cos(rtu_InBus1_Positions[3]);
  tmp_6 = std::cos(rtu_InBus1_Positions[5]);
  tmp_7 = std::sin(rtu_InBus1_Positions[4]);
  tmp_8 = std::cos(rtu_InBus1_Positions[4]);
  tmp_9 = std::sin(rtu_InBus1_Positions[5]);
  tmp_a = std::cos(rtu_InBus1_Positions[3]);
  tmp_b = std::cos(rtu_InBus1_Positions[5]);
  tmp_c = std::sin(rtu_InBus1_Positions[3]);
  tmp_d = std::sin(rtu_InBus1_Positions[5]);
  tmp_e = std::sin(rtu_InBus1_Positions[4]);
  D15_tmp_tmp = std::cos(rtu_InBus1_Positions[5]);
  D15_tmp_tmp_0 = std::sin(rtu_InBus1_Positions[3]);
  D46_tmp_tmp = std::cos(rtu_InBus1_Positions[3]);
  D46_tmp_tmp_0 = std::sin(rtu_InBus1_Positions[5]);
  D56_tmp_tmp_3 = std::sin(rtu_InBus1_Positions[4]);
  D46_tmp_tmp_1 = std::sin(rtu_InBus1_Positions[4]);
  D46_tmp_tmp_2 = std::cos(rtu_InBus1_Positions[4]);
  D46_tmp_tmp_7 = std::sin(rtu_InBus1_Positions[3]);
  D46_tmp_tmp_6 = std::cos(rtu_InBus1_Positions[3]);
  D46_tmp_tmp_8 = std::cos(rtu_InBus1_Positions[4]);
  smax_tmp = std::sin(rtu_InBus1_Positions[3]);
  D46_tmp_tmp_9 = std::tan(rtu_InBus1_Positions[4]);
  D46_tmp_tmp_a = std::cos(rtu_InBus1_Positions[3]);
  D46_tmp_tmp_b = std::tan(rtu_InBus1_Positions[4]);
  D56_tmp_tmp_1 = std::cos(rtu_InBus1_Positions[3]);
  D56_tmp_tmp = std::sin(rtu_InBus1_Positions[3]);
  D56_tmp_tmp_9 = std::cos(rtu_InBus1_Positions[4]);
  D56_tmp_tmp_6 = std::sin(rtu_InBus1_Positions[3]);
  D56_tmp_tmp_0 = std::cos(rtu_InBus1_Positions[3]);
  D56_tmp_tmp_2 = std::cos(rtu_InBus1_Positions[4]);

  /* :  BMinv = inv(BM); */
  std::memset(&x[0], 0, sizeof(real_T) << 6U);
  std::memset(&PD_B.BMinv[0], 0, sizeof(real_T) << 6U);
  x[0] = D46_tmp_v * D46_tmp_w;
  x[8] = tmp_0 * tmp_1 * tmp_2 + -D46_tmp_x * tmp;
  x[16] = tmp_5 * tmp_6 * tmp_7 + tmp_3 * tmp_4;
  x[24] = 0.0;
  x[32] = 0.0;
  x[40] = 0.0;
  x[1] = tmp_8 * tmp_9;
  x[9] = tmp_c * tmp_d * tmp_e + tmp_a * tmp_b;
  x[17] = D46_tmp_tmp * D46_tmp_tmp_0 * D56_tmp_tmp_3 + -D15_tmp_tmp *
    D15_tmp_tmp_0;
  x[25] = 0.0;
  x[33] = 0.0;
  x[41] = 0.0;
  x[2] = -D46_tmp_tmp_1;
  x[10] = D46_tmp_tmp_2 * D46_tmp_tmp_7;
  x[18] = D46_tmp_tmp_6 * D46_tmp_tmp_8;
  x[26] = 0.0;
  x[34] = 0.0;
  x[42] = 0.0;
  x[3] = 0.0;
  x[11] = 0.0;
  x[19] = 0.0;
  x[27] = 1.0;
  x[35] = smax_tmp * D46_tmp_tmp_9;
  x[43] = D46_tmp_tmp_a * D46_tmp_tmp_b;
  x[4] = 0.0;
  x[12] = 0.0;
  x[20] = 0.0;
  x[28] = 0.0;
  x[36] = D56_tmp_tmp_1;
  x[44] = -D56_tmp_tmp;
  x[5] = 0.0;
  x[13] = 0.0;
  x[21] = 0.0;
  x[29] = 0.0;
  x[37] = 1.0 / D56_tmp_tmp_9 * D56_tmp_tmp_6;
  x[45] = 1.0 / D56_tmp_tmp_2 * D56_tmp_tmp_0;
  x[54] = 1.0;
  x[55] = 0.0;
  x[62] = 0.0;
  x[63] = 1.0;
  for (ix = 0; ix < 8; ix++) {
    p[ix] = static_cast<int8_T>(ix + 1);
    ipiv[ix] = static_cast<int8_T>(ix + 1);
  }

  for (i = 0; i < 7; i++) {
    jj = i * 9;
    iy = 9 - i;
    b_ix = 0;
    ix = jj;
    smax = std::abs(x[jj]);
    for (d_k = 2; d_k < iy; d_k++) {
      s = std::abs(x[(ix + d_k) - 1]);
      if (s > smax) {
        b_ix = d_k - 1;
        smax = s;
      }
    }

    if (x[jj + b_ix] != 0.0) {
      if (b_ix != 0) {
        iy = i + b_ix;
        ipiv[i] = static_cast<int8_T>(iy + 1);
        b_ix = i;
        for (d_k = 0; d_k < 8; d_k++) {
          smax = x[b_ix];
          x[b_ix] = x[iy];
          x[iy] = smax;
          b_ix += 8;
          iy += 8;
        }
      }

      iy = (jj - i) + 8;
      ix = (((((iy - jj) - 1) / 2) << 1) + jj) + 2;
      b_ix = ix - 2;
      for (d_k = jj + 2; d_k <= b_ix; d_k += 2) {
        tmp_hw = _mm_loadu_pd(&x[d_k - 1]);
        tmp_hw = _mm_div_pd(tmp_hw, _mm_set1_pd(x[jj]));
        _mm_storeu_pd(&x[d_k - 1], tmp_hw);
      }

      for (d_k = ix; d_k <= iy; d_k++) {
        x[d_k - 1] /= x[jj];
      }
    }

    b_ix = 6 - i;
    ix = jj + 10;
    jy = jj + 8;
    for (d_k = 0; d_k <= b_ix; d_k++) {
      D46_tmp_v = x[(d_k << 3) + jy];
      if (D46_tmp_v != 0.0) {
        smax = -D46_tmp_v;
        c_ix = jj + 1;
        d = (ix - i) + 6;
        for (iy = ix; iy <= d; iy++) {
          x[iy - 1] += x[(c_ix + iy) - ix] * smax;
        }
      }

      ix += 8;
    }
  }

  for (i = 0; i < 7; i++) {
    ipiv_0 = ipiv[i];
    if (ipiv_0 > i + 1) {
      d_k = ipiv_0 - 1;
      jj = p[d_k];
      p[d_k] = p[i];
      p[i] = static_cast<int8_T>(jj);
    }
  }

  for (i = 0; i < 8; i++) {
    ipiv_0 = p[i];
    jy = (ipiv_0 - 1) << 3;
    PD_B.BMinv[i + jy] = 1.0;
    for (jj = i + 1; jj < 9; jj++) {
      ix = (jy + jj) - 1;
      if (PD_B.BMinv[ix] != 0.0) {
        for (d_k = jj + 1; d_k < 9; d_k++) {
          iy = (jy + d_k) - 1;
          PD_B.BMinv[iy] -= x[(((jj - 1) << 3) + d_k) - 1] * PD_B.BMinv[ix];
        }
      }
    }
  }

  /* MATLAB Function: '<S3>/PD Controller' incorporates:
   *  Constant: '<S3>/Kd'
   *  Constant: '<S3>/Kp'
   */
  /* :  kp_m = [kp(1) 0       0     0     0       0     0     0; */
  /* :          0     kp(2)   0     0     0       0     0     0; */
  /* :          0     0       kp(3) 0     0       0     0     0; */
  /* :          0     0       0     kp(4) 0       0     0     0; */
  /* :          0     0       0     0     kp(5)   0     0     0; */
  /* :          0     0       0     0     0       kp(6) 0     0; */
  /* :          0     0       0     0     0       0     kp(7) 0; */
  /* :          0     0       0     0     0       0     0     kp(8)]; */
  /* :  kd_m = [kd(1) 0       0     0     0       0     0     0; */
  /* :          0     kd(2)   0     0     0       0     0     0; */
  /* :          0     0       kd(3) 0     0       0     0     0; */
  /* :          0     0       0     kd(4) 0       0     0     0; */
  /* :          0     0       0     0     kd(5)   0     0     0; */
  /* :          0     0       0     0     0       kd(6) 0     0; */
  /* :          0     0       0     0     0       0     kd(7) 0; */
  /* :          0     0       0     0     0       0     0     kd(8)]; */
  /* :  u_aux = kp_m * e + kd_m * de; */
  tmp_hr[0] = rtP_PID.Kp[0];
  tmp_hr[8] = 0.0;
  tmp_hr[16] = 0.0;
  tmp_hr[24] = 0.0;
  tmp_hr[32] = 0.0;
  tmp_hr[40] = 0.0;
  tmp_hr[48] = 0.0;
  tmp_hr[56] = 0.0;
  tmp_hr[1] = 0.0;
  tmp_hr[9] = rtP_PID.Kp[1];
  tmp_hr[17] = 0.0;
  tmp_hr[25] = 0.0;
  tmp_hr[33] = 0.0;
  tmp_hr[41] = 0.0;
  tmp_hr[49] = 0.0;
  tmp_hr[57] = 0.0;
  tmp_hr[2] = 0.0;
  tmp_hr[10] = 0.0;
  tmp_hr[18] = rtP_PID.Kp[2];
  tmp_hr[26] = 0.0;
  tmp_hr[34] = 0.0;
  tmp_hr[42] = 0.0;
  tmp_hr[50] = 0.0;
  tmp_hr[58] = 0.0;
  tmp_hr[3] = 0.0;
  tmp_hr[11] = 0.0;
  tmp_hr[19] = 0.0;
  tmp_hr[27] = rtP_PID.Kp[3];
  tmp_hr[35] = 0.0;
  tmp_hr[43] = 0.0;
  tmp_hr[51] = 0.0;
  tmp_hr[59] = 0.0;
  tmp_hr[4] = 0.0;
  tmp_hr[12] = 0.0;
  tmp_hr[20] = 0.0;
  tmp_hr[28] = 0.0;
  tmp_hr[36] = rtP_PID.Kp[4];
  tmp_hr[44] = 0.0;
  tmp_hr[52] = 0.0;
  tmp_hr[60] = 0.0;
  tmp_hr[5] = 0.0;
  tmp_hr[13] = 0.0;
  tmp_hr[21] = 0.0;
  tmp_hr[29] = 0.0;
  tmp_hr[37] = 0.0;
  tmp_hr[45] = rtP_PID.Kp[5];
  tmp_hr[53] = 0.0;
  tmp_hr[61] = 0.0;
  tmp_hr[6] = 0.0;
  tmp_hr[14] = 0.0;
  tmp_hr[22] = 0.0;
  tmp_hr[30] = 0.0;
  tmp_hr[38] = 0.0;
  tmp_hr[46] = 0.0;
  tmp_hr[54] = rtP_PID.Kp[6];
  tmp_hr[62] = 0.0;
  tmp_hr[7] = 0.0;
  tmp_hr[15] = 0.0;
  tmp_hr[23] = 0.0;
  tmp_hr[31] = 0.0;
  tmp_hr[39] = 0.0;
  tmp_hr[47] = 0.0;
  tmp_hr[55] = 0.0;
  tmp_hr[63] = rtP_PID.Kp[7];
  tmp_hu[0] = rtP_PID.Kd[0];
  tmp_hu[8] = 0.0;
  tmp_hu[16] = 0.0;
  tmp_hu[24] = 0.0;
  tmp_hu[32] = 0.0;
  tmp_hu[40] = 0.0;
  tmp_hu[48] = 0.0;
  tmp_hu[56] = 0.0;
  tmp_hu[1] = 0.0;
  tmp_hu[9] = rtP_PID.Kd[1];
  tmp_hu[17] = 0.0;
  tmp_hu[25] = 0.0;
  tmp_hu[33] = 0.0;
  tmp_hu[41] = 0.0;
  tmp_hu[49] = 0.0;
  tmp_hu[57] = 0.0;
  tmp_hu[2] = 0.0;
  tmp_hu[10] = 0.0;
  tmp_hu[18] = rtP_PID.Kd[2];
  tmp_hu[26] = 0.0;
  tmp_hu[34] = 0.0;
  tmp_hu[42] = 0.0;
  tmp_hu[50] = 0.0;
  tmp_hu[58] = 0.0;
  tmp_hu[3] = 0.0;
  tmp_hu[11] = 0.0;
  tmp_hu[19] = 0.0;
  tmp_hu[27] = rtP_PID.Kd[3];
  tmp_hu[35] = 0.0;
  tmp_hu[43] = 0.0;
  tmp_hu[51] = 0.0;
  tmp_hu[59] = 0.0;
  tmp_hu[4] = 0.0;
  tmp_hu[12] = 0.0;
  tmp_hu[20] = 0.0;
  tmp_hu[28] = 0.0;
  tmp_hu[36] = rtP_PID.Kd[4];
  tmp_hu[44] = 0.0;
  tmp_hu[52] = 0.0;
  tmp_hu[60] = 0.0;
  tmp_hu[5] = 0.0;
  tmp_hu[13] = 0.0;
  tmp_hu[21] = 0.0;
  tmp_hu[29] = 0.0;
  tmp_hu[37] = 0.0;
  tmp_hu[45] = rtP_PID.Kd[5];
  tmp_hu[53] = 0.0;
  tmp_hu[61] = 0.0;
  tmp_hu[6] = 0.0;
  tmp_hu[14] = 0.0;
  tmp_hu[22] = 0.0;
  tmp_hu[30] = 0.0;
  tmp_hu[38] = 0.0;
  tmp_hu[46] = 0.0;
  tmp_hu[54] = rtP_PID.Kd[6];
  tmp_hu[62] = 0.0;
  tmp_hu[7] = 0.0;
  tmp_hu[15] = 0.0;
  tmp_hu[23] = 0.0;
  tmp_hu[31] = 0.0;
  tmp_hu[39] = 0.0;
  tmp_hu[47] = 0.0;
  tmp_hu[55] = 0.0;
  tmp_hu[63] = rtP_PID.Kd[7];
  for (i = 0; i < 8; i++) {
    /* MATLAB Function: '<Root>/GetBInvMatrix' */
    iy = i << 3;
    for (jj = 7; jj >= 0; jj--) {
      b_ix = jj << 3;
      ix = jj + iy;
      D46_tmp_v = PD_B.BMinv[ix];
      if (D46_tmp_v != 0.0) {
        PD_B.BMinv[ix] = D46_tmp_v / x[jj + b_ix];
        for (d_k = 0; d_k < jj; d_k++) {
          jy = d_k + iy;
          PD_B.BMinv[jy] -= x[d_k + b_ix] * PD_B.BMinv[ix];
        }
      }
    }

    /* Sum: '<S5>/Minus1' incorporates:
     *  Sum: '<S5>/Minus'
     */
    tmp_hw = _mm_sub_pd(_mm_set_pd(rtu_InBus_dqd[i], rtu_InBus_qd[i]),
                        _mm_set_pd(rtu_InBus1_Velocities[i],
      rtu_InBus1_Positions[i]));
    _mm_storeu_pd(&tmp_hv[0], tmp_hw);

    /* Sum: '<S5>/Minus' */
    PD_B.error_q[i] = tmp_hv[0];

    /* Sum: '<S5>/Minus1' */
    PD_B.error_dq[i] = tmp_hv[1];

    /* MATLAB Function: '<S3>/PD Controller' */
    tmp_hs[i] = 0.0;
  }

  /* MATLAB Function: '<S3>/PD Controller' incorporates:
   *  Sum: '<S5>/Minus'
   *  Sum: '<S5>/Minus1'
   */
  for (ix = 0; ix < 8; ix++) {
    D46_tmp_v = PD_B.error_q[ix];
    for (i = 0; i <= 6; i += 2) {
      tmp_hw = _mm_loadu_pd(&tmp_hr[(ix << 3) + i]);
      tmp_hw = _mm_mul_pd(tmp_hw, _mm_set1_pd(D46_tmp_v));
      tmp_i3 = _mm_loadu_pd(&tmp_hs[i]);
      tmp_hw = _mm_add_pd(tmp_hw, tmp_i3);
      _mm_storeu_pd(&tmp_hs[i], tmp_hw);
    }

    tmp_ht[ix] = 0.0;
  }

  for (ix = 0; ix < 8; ix++) {
    D46_tmp_v = PD_B.error_dq[ix];
    for (i = 0; i <= 6; i += 2) {
      tmp_hw = _mm_loadu_pd(&tmp_hu[(ix << 3) + i]);
      tmp_hw = _mm_mul_pd(tmp_hw, _mm_set1_pd(D46_tmp_v));
      tmp_i3 = _mm_loadu_pd(&tmp_ht[i]);
      tmp_hw = _mm_add_pd(tmp_hw, tmp_i3);
      _mm_storeu_pd(&tmp_ht[i], tmp_hw);
    }
  }

  for (i = 0; i <= 6; i += 2) {
    tmp_hw = _mm_loadu_pd(&tmp_hs[i]);
    tmp_i3 = _mm_loadu_pd(&tmp_ht[i]);
    tmp_hw = _mm_add_pd(tmp_hw, tmp_i3);
    _mm_storeu_pd(&PD_B.u_aux[i], tmp_hw);

    /* Sum: '<S3>/Sum' */
    tmp_i3 = _mm_loadu_pd(&rtu_InBus_ddqd[i]);
    tmp_hw = _mm_add_pd(tmp_i3, tmp_hw);

    /* Sum: '<S3>/Sum' */
    _mm_storeu_pd(&PD_B.Sum[i], tmp_hw);

    /* Sum: '<S3>/Add1' incorporates:
     *  Sum: '<S3>/Sum'
     */
    tmp_i3 = _mm_loadu_pd(&PD_B.fx[i]);
    tmp_hw = _mm_sub_pd(tmp_hw, tmp_i3);

    /* Sum: '<S3>/Add1' */
    _mm_storeu_pd(&PD_B.Add1[i], tmp_hw);
  }

  /* Product: '<S3>/Matrix Multiply' incorporates:
   *  Sum: '<S3>/Add1'
   */
  std::memcpy(&x[0], &PD_B.ginv[0], sizeof(real_T) << 6U);
  for (ix = 0; ix < 8; ix++) {
    tmp_hs[ix] = PD_B.Add1[ix];
    PD_B.u[ix] = 0.0;
  }

  for (ix = 0; ix < 8; ix++) {
    D46_tmp_v = tmp_hs[ix];
    for (i = 0; i <= 6; i += 2) {
      tmp_hw = _mm_loadu_pd(&x[(ix << 3) + i]);
      tmp_hw = _mm_mul_pd(tmp_hw, _mm_set1_pd(D46_tmp_v));
      tmp_i3 = _mm_loadu_pd(&PD_B.u[i]);
      tmp_hw = _mm_add_pd(tmp_hw, tmp_i3);
      _mm_storeu_pd(&PD_B.u[i], tmp_hw);
    }
  }

  /* End of Product: '<S3>/Matrix Multiply' */

  /* Product: '<Root>/Matrix Multiply' incorporates:
   *  Product: '<S3>/Matrix Multiply'
   */
  std::memcpy(&x[0], &PD_B.BMinv[0], sizeof(real_T) << 6U);
  for (ix = 0; ix < 8; ix++) {
    tmp_hs[ix] = PD_B.u[ix];
    rty_Output2[ix] = 0.0;
  }

  for (ix = 0; ix < 8; ix++) {
    D46_tmp_v = tmp_hs[ix];
    for (i = 0; i <= 6; i += 2) {
      tmp_hw = _mm_loadu_pd(&x[(ix << 3) + i]);
      tmp_hw = _mm_mul_pd(tmp_hw, _mm_set1_pd(D46_tmp_v));
      tmp_i3 = _mm_loadu_pd(&rty_Output2[i]);
      tmp_hw = _mm_add_pd(tmp_hw, tmp_i3);
      _mm_storeu_pd(&rty_Output2[i], tmp_hw);
    }
  }

  /* End of Product: '<Root>/Matrix Multiply' */
}

/* Constructor */
PD::PD() :
  PD_B(),
  PD_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
/* Currently there is no destructor body generated.*/
PD::~PD() = default;

/* Real-Time Model get method */
RT_MODEL_PD_T * PD::getRTM()
{
  return (&PD_M);
}

/* member function to initialize Real-Time model */
void PD::initializeRTM(RTWSolverInfo *rt_solverInfo)
{
  /* initialize RTWSolverInfo */
  (&PD_M)->solverInfo = (rt_solverInfo);

  /* Set the Timing fields to the appropriate data in the RTWSolverInfo */
  rtmSetSimTimeStepPointer((&PD_M), rtsiGetSimTimeStepPtr((&PD_M)->solverInfo));
  (&PD_M)->Timing.stepSize0 = (rtsiGetStepSize((&PD_M)->solverInfo));
}

/* member function to setup error status pointer */
void PD::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&PD_M), rt_errorStatus);
}
