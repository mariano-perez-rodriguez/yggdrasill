#include "Xsg.h"


namespace {
  /*
   * Modulus candidates
   *
   * n     2^n   - 1  :  Factorization
   * 521   2^521 - 1  :  6864797660130609714981900799081393217269435300143305409394463459185543183397656052122559640661454554977296311391480858037121987999716643812574028291115057151
   * 523   2^523 - 1  :  160188778313202118610543685368878688932828701136501444932217468039063, 171417691861249198128317096534322116476165056718630345094896620367860006486977101859504089
   * 541   2^541 - 1  :  4312790327, 6115209994009, 77146448294831869472151022106713, 904106555381898703253733254107256591, 3913112911835820709255943886069525362580351752909309688547154382752707879
   * 547   2^547 - 1  :  5471, 172720604638150729, 157552196128597543991, 3094370432032805355177230433270065636934209000089709476056046201975893944504526523646181882472019182454441940262575164313583
   * 557   2^557 - 1  :  3343, 21993703, 4565508951414453792719, 22053236096920219270632521586535711, 63725217520100446091019213316114800470054259870518161822841838235099774015887061706672583915057828311
   * 563   2^563 - 1  :  2815747080256641401887817, 13299213974872825932452460424235657, 806246686530274231554002548822879844631710799886320977786718630531739958469131883287342678637275814925394111503
   * 569   2^569 - 1  :  15854617, 55470673, 182602768015690099110572536951, 110582329556343704552404016904356632250881, 108806602929626417274819133540757472113515266666479405303620102624927964940643869698641
   * 571   2^571 - 1  :  5711, 27409, 6969336604531667168509871230100794095801832527002849548226132675916172927, 7084851186360580941633572744569751943590093912197024061201633650193388126309578906138706239
   * 577   2^577 - 1  :  3463, 132305774316967, 1079633141772892852450713464662329764119217100464362618290526362027911012565069142996396993157133020422681868025602819574600599624729277860300320636162145551
   * 587   2^587 - 1  :  554129, 2926783, 39483330766889, 73208283304744901303, 3728298863422039632638351, 28981531265700436474908668605764037292283479533071482196860868875487797459833848867410473799526014756969233
   *
   * These were chosen for the following reasons:
   *  - all the "n"s are greater than 512,
   *  - all the "n"s are prime numbers,
   *  - the generated cycle lengths (ie. 2^n - 1) share no common factors between them,
   *  - the smallest factor is 3343, far beyond the biggest set of contiguous steps taken at any given time at a single LFSR
   *
   * Hexes for primitive polynomials:
   *
   * 521: 1986842c7f1620218c78e583637aa0baf82558ef35d875948b22ce317ba47cce076f48541f1a593896ee3f9e3c9541b4d3e65941170c721e4d5c879a51bff933e1f
   * 523: 6105ba99822ea4b0b57c26d5aa74c6b17f150b4c33147b4bd570e9aa1cbc663291ef6185805aa700b61672751f068eda9a1698c62b3fe4e7b034f3b8d899dfcfd92
   * 541: 1ec09c4098c55499ac20b3925f4297c214e193d3dae3cea7f18afc422f315b82967b4b0f2c6bb5c4ae568ce242144d568731dbfeeb91d60ba4af6380a7428e7567c7e2df
   * 547: 64f78024e326cc0d2dff541adc8737fc1843235fdb1feade3971cb90a49a8d2e1327babeaba4323e7481208590446fc35f9b2aa49a3a945b19e0a511148fbca3693f7a62b
   * 557: 16e4b48a1c95a2964c7e25d6d874610f3c8b062e65c3612a0159ff1db7cc37ca400b419d54f6862d9c9e99cea9c7c631d58c2d4b1fb3898ca473ad780d5cb815897e4c2fdffc
   * 563: 7bd42d0d9139a43b88782e4528fdc9405f247122f963d317ca59b8919e8b3fd0d9c03f6638fc6cd95a415798c81f7e68f6c434913791b05f117f2277c2d09aa33140a5eee6ce9
   * 569: 1e4b1bd8f20bdbc87160d29b239e5145417d54e0f3141017e024ebd6a48c1e411cac4094e799f4b16b30b1b2b1fec135d2f3f9ad4ff326239f9ee9fe2595a5260d34d25dec0daa3
   * 571: 524e4906c9a6e04efd9320a53d26f87f769e0c22a112ac5345db2a7f7d506d446e92d449ce738bb9f6569ac792b868968aab13563fa59125986482bee5053f795b8a916b713f8c4
   * 577: 1b6fbcc26ce53833c854c5ce494e6cce36da5f40fc8a859727d2d292fb9aed51aedc1354f08e334588906bf4810f3faa2fe9f7be426a08758271502b7d3e39d1d03542015f2e120ee
   * 587: 721f51d38e8877b135aa1f131d421e9008761a6f662c7675d9934e22636e34e33ee964b6bbbc270c31e800f82f18669753260fb9c0a616b1f763cf3e32c8394e9215b3d9e08975a56e7
   *
   */

  /**
   * Mother multipliers for different prime modulus
   *
   */
  /*
   std::array<std::uint64_t, 67> mothers521 = { 15, 23, 27, 35, 38, 41, 48, 70, 76, 82, 87, 95, 103, 111, 115, 136, 137, 147, 149, 153, 154, 157, 171, 178, 184, 186, 203, 209, 216, 222, 223, 241, 262, 264, 270, 277, 282, 294, 297, 303, 305, 312, 314, 335, 337, 339, 344, 354, 357, 374, 382, 399, 410, 412, 428, 429, 435, 442, 444, 445, 448, 467, 493, 494, 504, 514, 515 };
   */
  std::array<std::uint64_t, 84> mothers523 = { 15, 16, 23, 25, 28, 31, 36, 49, 66, 68, 74, 89, 91, 96, 100, 102, 107, 111, 117, 131, 135, 143, 151, 157, 166, 169, 171, 175, 176, 185, 190, 201, 202, 207, 209, 221, 223, 235, 241, 249, 255, 257, 258, 275, 278, 281, 287, 290, 292, 296, 301, 318, 319, 324, 326, 339, 356, 367, 376, 377, 381, 383, 391, 395, 419, 425, 426, 430, 437, 438, 439, 440, 443, 448, 454, 467, 475, 476, 478, 489, 493, 505, 518, 521 };
  std::array<std::uint64_t, 66> mothers541 = { 18, 24, 37, 62, 65, 67, 68, 73, 83, 91, 96, 98, 117, 127, 152, 153, 181, 197, 206, 208, 218, 220, 224, 248, 261, 263, 267, 280, 283, 284, 291, 293, 297, 318, 321, 328, 335, 344, 358, 365, 383, 385, 388, 403, 409, 410, 413, 415, 427, 428, 434, 443, 445, 458, 468, 473, 474, 476, 479, 486, 490, 511, 523, 527, 528, 531 };
  std::array<std::uint64_t, 71> mothers547 = { 4, 15, 16, 19, 25, 36, 49, 60, 66, 74, 82, 86, 97, 99, 115, 116, 118, 135, 137, 142, 143, 144, 160, 171, 177, 183, 193, 202, 206, 208, 214, 225, 227, 249, 250, 256, 266, 275, 287, 289, 313, 317, 324, 326, 328, 336, 344, 346, 361, 385, 394, 395, 400, 401, 406, 413, 438, 443, 452, 455, 489, 490, 497, 499, 502, 504, 514, 515, 530, 535, 542 };
  std::array<std::uint64_t, 88> mothers557 = { 3, 5, 11, 13, 14, 21, 31, 41, 44, 52, 86, 87, 89, 91, 92, 95, 107, 108, 125, 126, 128, 134, 136, 147, 152, 162, 166, 176, 177, 186, 189, 191, 192, 200, 224, 228, 237, 238, 247, 264, 275, 279, 286, 287, 291, 300, 315, 319, 325, 331, 333, 340, 346, 348, 350, 356, 363, 365, 369, 393, 396, 405, 409, 427, 432, 437, 447, 449, 454, 459, 466, 470, 472, 473, 477, 479, 501, 504, 505, 507, 509, 510, 519, 520, 530, 534, 544, 549 };
  /*
  std::array<std::uint64_t, 92> mothers563 = { 7, 13, 16, 21, 39, 58, 59, 61, 71, 75, 86, 92, 101, 108, 113, 120, 133, 141, 144, 145, 146, 147, 149, 166, 169, 170, 171, 174, 175, 178, 181, 190, 191, 201, 204, 207, 209, 211, 213, 215, 218, 221, 230, 231, 232, 236, 243, 244, 246, 251, 253, 256, 269, 273, 276, 277, 278, 302, 303, 314, 323, 330, 336, 351, 361, 363, 365, 383, 395, 399, 406, 411, 412, 415, 421, 424, 427, 437, 448, 454, 459, 467, 468, 475, 509, 510, 517, 518, 526, 537, 557, 558 };
  std::array<std::uint64_t, 70> mothers569 = { 19, 22, 48, 53, 58, 89, 96, 103, 115, 123, 145, 157, 171, 173, 184, 189, 190, 193, 195, 201, 204, 216, 217, 220, 230, 236, 237, 247, 265, 271, 279, 290, 298, 299, 303, 308, 321, 326, 329, 333, 336, 337, 349, 352, 358, 359, 375, 377, 382, 388, 401, 413, 417, 419, 421, 446, 463, 464, 475, 510, 516, 518, 523, 527, 530, 538, 545, 550, 563, 566 };
  std::array<std::uint64_t, 58> mothers571 = { 13, 21, 25, 34, 44, 45, 52, 54, 57, 66, 78, 96, 97, 100, 119, 126, 133, 139, 141, 145, 155, 172, 173, 202, 204, 213, 222, 224, 227, 237, 261, 273, 274, 279, 280, 287, 289, 312, 322, 329, 332, 371, 374, 394, 403, 424, 469, 470, 478, 495, 497, 499, 504, 518, 531, 532, 538, 568 };
  std::array<std::uint64_t, 91> mothers577 = { 5, 7, 10, 15, 21, 28, 40, 43, 55, 58, 61, 77, 84, 89, 101, 103, 104, 116, 129, 137, 158, 164, 165, 172, 173, 183, 189, 211, 217, 218, 222, 226, 227, 229, 230, 231, 233, 238, 245, 247, 255, 257, 267, 269, 270, 278, 285, 292, 299, 308, 309, 312, 327, 332, 346, 350, 355, 366, 388, 389, 394, 399, 402, 405, 409, 411, 412, 413, 429, 440, 443, 455, 460, 464, 474, 476, 483, 487, 488, 492, 495, 497, 500, 504, 519, 522, 538, 547, 549, 556, 567 };
  std::array<std::uint64_t, 83> mothers578 = { 10, 17, 21, 26, 29, 31, 36, 43, 53, 55, 66, 74, 83, 84, 95, 101, 108, 112, 137, 141, 144, 147, 151, 160, 172, 179, 194, 197, 203, 217, 218, 220, 222, 234, 236, 237, 256, 268, 270, 280, 289, 299, 303, 324, 328, 345, 347, 352, 356, 359, 366, 372, 385, 387, 397, 404, 413, 414, 431, 442, 448, 453, 454, 455, 459, 460, 482, 484, 485, 490, 496, 511, 516, 525, 537, 546, 563, 567, 568, 572, 573, 574, 579 };
   */

  /**
   * Hexadecimal representation of primitive generators for different prime modulus
   *
   */
  std::string hexGen521 = "1986842c7f1620218c78e583637aa0baf82558ef35d875948b22ce317ba47cce076f48541f1a593896ee3f9e3c9541b4d3e65941170c721e4d5c879a51bff933e1f";
  std::string hexGen523 = "6105ba99822ea4b0b57c26d5aa74c6b17f150b4c33147b4bd570e9aa1cbc663291ef6185805aa700b61672751f068eda9a1698c62b3fe4e7b034f3b8d899dfcfd92";
  std::string hexGen541 = "1ec09c4098c55499ac20b3925f4297c214e193d3dae3cea7f18afc422f315b82967b4b0f2c6bb5c4ae568ce242144d568731dbfeeb91d60ba4af6380a7428e7567c7e2df";
  std::string hexGen547 = "64f78024e326cc0d2dff541adc8737fc1843235fdb1feade3971cb90a49a8d2e1327babeaba4323e7481208590446fc35f9b2aa49a3a945b19e0a511148fbca3693f7a62b";
  std::string hexGen557 = "16e4b48a1c95a2964c7e25d6d874610f3c8b062e65c3612a0159ff1db7cc37ca400b419d54f6862d9c9e99cea9c7c631d58c2d4b1fb3898ca473ad780d5cb815897e4c2fdffc";
  /*
  std::string hexGen563 = "7bd42d0d9139a43b88782e4528fdc9405f247122f963d317ca59b8919e8b3fd0d9c03f6638fc6cd95a415798c81f7e68f6c434913791b05f117f2277c2d09aa33140a5eee6ce9";
  std::string hexGen569 = "1e4b1bd8f20bdbc87160d29b239e5145417d54e0f3141017e024ebd6a48c1e411cac4094e799f4b16b30b1b2b1fec135d2f3f9ad4ff326239f9ee9fe2595a5260d34d25dec0daa3";
  std::string hexGen571 = "524e4906c9a6e04efd9320a53d26f87f769e0c22a112ac5345db2a7f7d506d446e92d449ce738bb9f6569ac792b868968aab13563fa59125986482bee5053f795b8a916b713f8c4";
  std::string hexGen577 = "1b6fbcc26ce53833c854c5ce494e6cce36da5f40fc8a859727d2d292fb9aed51aedc1354f08e334588906bf4810f3faa2fe9f7be426a08758271502b7d3e39d1d03542015f2e120ee";
  std::string hexGen587 = "721f51d38e8877b135aa1f131d421e9008761a6f662c7675d9934e22636e34e33ee964b6bbbc270c31e800f82f18669753260fb9c0a616b1f763cf3e32c8394e9215b3d9e08975a56e7";
   */

  /**
   * Successive prefixes of the binary expansion of Pi as hexadecimal strings
   *
   */
  std::string hexPi521 = "121fb54442d18469898cc51701b839a252049c1114cf98e804177d4c76273644a29410f31c6809bbdf2a33679a748636605614dbe4be286e9fc26adadaa3848bc90";
  std::string hexPi523 = "5b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7edee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3dc2007cb8a163bf0598da48361c55d39a69163f";
  std::string hexPi541 = "151fa499ebf06caba47b9475b2c38c5e6ac410aa5773daa520ee12d2cdace186a9c95793009e2e8d811943042f86520bc8c5c6d9c77c73cee58301d0c07364f0745d80f4";
  std::string hexPi547 = "28fb5c55df06f4c52c9de2bcbf6955817183995497cea956ae515d2261898fa051015728e5a8aaac42dad33170d04507a33a85521abdf1cba64ecfb850458dbef0a8aea71";
  std::string hexPi557 = "0aeba0c18fb672e1f0b4dc3c98f57eb5d19b61267ae3d1929c0944ac33b9dc7a44c35a5dcd7e25ff40db31410c9b0ec04e67d90d4c8a43e56302ef6401977c22eaef4c2bad8e";
  /*
  std::string hexPi563 = "70988c0bad946e208e24fa074e5ab3143db5bfce0fd108e4b82d120a92108011a723c12a787e6d788719a10bdba5b2699c327186af4e23c1a946834b6150bda2583e9ca2ad44c";
  std::string hexPi569 = "1d1b77785b609bd1df25d1df8283f7d954c50f8b28e9cd780bb33652c9f412187444677430ca2b7cfda3ec252e19dc5af5f7037baec42e09039a00d224fab60b5532769d5311b1f";
  std::string hexPi571 = "5dc186ffb7dc90a6c08f4df435c93402849236c3fab4d27c7026c1d4dcb2602646dec9751e763dba37bdf8ff9406ad9e530ee5db382f413001aeb06a53ed9027d831179727b0865";
  std::string hexPi577 = "151231b47db7d79f3629da899cd9759da97637b6fe288fcd984a966640a2a257af5e84df71e8026f19a57eb30794038c9725d9e065d42ba2e43a07e905af9cdce9fdedaabce05e8d3";
  std::string hexPi587 = "00c82b5a84031900b1c9e59e7c97fbec7e8f323a97a7e36cc88be0f1d45b7ff585ac54bd407b22b4154aacc8f6d7ebf48e1d814cc5ed20f8037e0a79715eef29be32806a1d58bb7c5da";
   */
}


/**
 * Return a distilled XSG from a key
 *
 * Distillation works by accepting or creating a bootstrap XSG, feeding it
 * the given key, and using it as a PRNG to generate (in order):
 *  - LFSR initial states,
 *  - mother multipliers,
 *  - offsets, and
 *  - initial values,
 * the generators used are the canonical ones of orders 521, 523, 541, 547,
 * and 557.
 *
 * @param key   The key to use for distilling
 * @param boot  The bootstrap XSG to use (the canonical one if none given)
 * @return the created bootstrap XSG
 */
Xsg512 distillXsg(std::string key) noexcept {
  Xsg512 boot = Xsg512(
    Lfsr<521>(hexPi521, hexGen521), false,
    Lfsr<523>(hexPi523, hexGen523),
    Icg::deriveFromMother(523, mothers523[ 0],   2,  0),
    Icg::deriveFromMother(523, mothers523[ 1],   3,  1),
    Icg::deriveFromMother(523, mothers523[ 2],   5,  2),
    Icg::deriveFromMother(523, mothers523[ 3],   7,  3),
    Icg::deriveFromMother(523, mothers523[ 4],  11,  4),
    Icg::deriveFromMother(523, mothers523[ 5],  13,  5),
    Icg::deriveFromMother(523, mothers523[ 6],  17,  6),
    Icg::deriveFromMother(523, mothers523[ 7],  19,  7),
    Icg::deriveFromMother(523, mothers523[ 8],  22,  8),
    Lfsr<541>(hexPi541, hexGen541),
    Icg::deriveFromMother(541, mothers541[ 9],  31,  9),
    Icg::deriveFromMother(541, mothers541[10],  37, 10),
    Icg::deriveFromMother(541, mothers541[11],  41, 11),
    Icg::deriveFromMother(541, mothers541[12],  43, 12),
    Icg::deriveFromMother(541, mothers541[13],  47, 13),
    Icg::deriveFromMother(541, mothers541[14],  53, 14),
    Icg::deriveFromMother(541, mothers541[15],  59, 15),
    Icg::deriveFromMother(541, mothers541[16],  61, 16),
    Icg::deriveFromMother(541, mothers541[17],  67, 17),
    Lfsr<547>(hexPi547, hexGen547),
    Icg::deriveFromMother(547, mothers547[18],  71, 18),
    Icg::deriveFromMother(547, mothers547[19],  73, 19),
    Icg::deriveFromMother(547, mothers547[20],  79, 20),
    Icg::deriveFromMother(547, mothers547[21],  83, 21),
    Icg::deriveFromMother(547, mothers547[22],  89, 22),
    Icg::deriveFromMother(547, mothers547[23],  97, 23),
    Icg::deriveFromMother(547, mothers547[24], 101, 24),
    Icg::deriveFromMother(547, mothers547[25], 103, 25),
    Icg::deriveFromMother(547, mothers547[26], 107, 26),
    Lfsr<557>(hexPi557, hexGen557),
    Icg::deriveFromMother(557, mothers557[27], 109, 27),
    Icg::deriveFromMother(557, mothers557[28], 113, 28),
    Icg::deriveFromMother(557, mothers557[29], 127, 29),
    Icg::deriveFromMother(557, mothers557[30], 131, 30),
    Icg::deriveFromMother(557, mothers557[31], 137, 31),
    Icg::deriveFromMother(557, mothers557[32], 139, 32),
    Icg::deriveFromMother(557, mothers557[33], 149, 33),
    Icg::deriveFromMother(557, mothers557[34], 151, 34),
    Icg::deriveFromMother(557, mothers557[35], 157, 35)
  ).blend(4, true);
  return distillXsg(key, boot);
}
Xsg512 distillXsg(std::string key, Xsg512 &boot) noexcept {
  // inject key
  boot.inject(key, 4);

  // extract LFSR initial states
  std::bitset<521> m;  for (std::size_t i = 0; i < 521; i++) {  m[i] = boot.next(); }
  std::bitset<523> s0; for (std::size_t i = 0; i < 523; i++) { s0[i] = boot.next(); }
  std::bitset<541> s1; for (std::size_t i = 0; i < 541; i++) { s1[i] = boot.next(); }
  std::bitset<547> s2; for (std::size_t i = 0; i < 547; i++) { s2[i] = boot.next(); }
  std::bitset<557> s3; for (std::size_t i = 0; i < 557; i++) { s3[i] = boot.next(); }

  // extract multipliers
  std::uint64_t as0l1 = mothers523[boot.rand(84)], as0m1 = mothers523[boot.rand(84)], as0h1 = mothers523[boot.rand(84)];
  std::uint64_t as0l2 = mothers523[boot.rand(84)], as0m2 = mothers523[boot.rand(84)], as0h2 = mothers523[boot.rand(84)];
  std::uint64_t as0l3 = mothers523[boot.rand(84)], as0m3 = mothers523[boot.rand(84)], as0h3 = mothers523[boot.rand(84)];
  std::uint64_t as1l0 = mothers541[boot.rand(66)], as1m0 = mothers541[boot.rand(66)], as1h0 = mothers541[boot.rand(66)];
  std::uint64_t as1l2 = mothers541[boot.rand(66)], as1m2 = mothers541[boot.rand(66)], as1h2 = mothers541[boot.rand(66)];
  std::uint64_t as1l3 = mothers541[boot.rand(66)], as1m3 = mothers541[boot.rand(66)], as1h3 = mothers541[boot.rand(66)];
  std::uint64_t as2l0 = mothers547[boot.rand(71)], as2m0 = mothers547[boot.rand(71)], as2h0 = mothers547[boot.rand(71)];
  std::uint64_t as2l1 = mothers547[boot.rand(71)], as2m1 = mothers547[boot.rand(71)], as2h1 = mothers547[boot.rand(71)];
  std::uint64_t as2l3 = mothers547[boot.rand(71)], as2m3 = mothers547[boot.rand(71)], as2h3 = mothers547[boot.rand(71)];
  std::uint64_t as3l0 = mothers557[boot.rand(88)], as3m0 = mothers557[boot.rand(88)], as3h0 = mothers557[boot.rand(88)];
  std::uint64_t as3l1 = mothers557[boot.rand(88)], as3m1 = mothers557[boot.rand(88)], as3h1 = mothers557[boot.rand(88)];
  std::uint64_t as3l2 = mothers557[boot.rand(88)], as3m2 = mothers557[boot.rand(88)], as3h2 = mothers557[boot.rand(88)];

  // extract offsets
  std::uint64_t cs0l1 = 1 + boot.rand(522), cs0m1 = 1 + boot.rand(522), cs0h1 = 1 + boot.rand(522);
  std::uint64_t cs0l2 = 1 + boot.rand(522), cs0m2 = 1 + boot.rand(522), cs0h2 = 1 + boot.rand(522);
  std::uint64_t cs0l3 = 1 + boot.rand(522), cs0m3 = 1 + boot.rand(522), cs0h3 = 1 + boot.rand(522);
  std::uint64_t cs1l0 = 1 + boot.rand(540), cs1m0 = 1 + boot.rand(540), cs1h0 = 1 + boot.rand(540);
  std::uint64_t cs1l2 = 1 + boot.rand(540), cs1m2 = 1 + boot.rand(540), cs1h2 = 1 + boot.rand(540);
  std::uint64_t cs1l3 = 1 + boot.rand(540), cs1m3 = 1 + boot.rand(540), cs1h3 = 1 + boot.rand(540);
  std::uint64_t cs2l0 = 1 + boot.rand(546), cs2m0 = 1 + boot.rand(546), cs2h0 = 1 + boot.rand(546);
  std::uint64_t cs2l1 = 1 + boot.rand(546), cs2m1 = 1 + boot.rand(546), cs2h1 = 1 + boot.rand(546);
  std::uint64_t cs2l3 = 1 + boot.rand(546), cs2m3 = 1 + boot.rand(546), cs2h3 = 1 + boot.rand(546);
  std::uint64_t cs3l0 = 1 + boot.rand(556), cs3m0 = 1 + boot.rand(556), cs3h0 = 1 + boot.rand(556);
  std::uint64_t cs3l1 = 1 + boot.rand(556), cs3m1 = 1 + boot.rand(556), cs3h1 = 1 + boot.rand(556);
  std::uint64_t cs3l2 = 1 + boot.rand(556), cs3m2 = 1 + boot.rand(556), cs3h2 = 1 + boot.rand(556);

  // extract initial values
  std::uint64_t is0l1 = boot.rand(523), is0m1 = boot.rand(523), is0h1 = boot.rand(523);
  std::uint64_t is0l2 = boot.rand(523), is0m2 = boot.rand(523), is0h2 = boot.rand(523);
  std::uint64_t is0l3 = boot.rand(523), is0m3 = boot.rand(523), is0h3 = boot.rand(523);
  std::uint64_t is1l0 = boot.rand(541), is1m0 = boot.rand(541), is1h0 = boot.rand(541);
  std::uint64_t is1l2 = boot.rand(541), is1m2 = boot.rand(541), is1h2 = boot.rand(541);
  std::uint64_t is1l3 = boot.rand(541), is1m3 = boot.rand(541), is1h3 = boot.rand(541);
  std::uint64_t is2l0 = boot.rand(547), is2m0 = boot.rand(547), is2h0 = boot.rand(547);
  std::uint64_t is2l1 = boot.rand(547), is2m1 = boot.rand(547), is2h1 = boot.rand(547);
  std::uint64_t is2l3 = boot.rand(547), is2m3 = boot.rand(547), is2h3 = boot.rand(547);
  std::uint64_t is3l0 = boot.rand(557), is3m0 = boot.rand(557), is3h0 = boot.rand(557);
  std::uint64_t is3l1 = boot.rand(557), is3m1 = boot.rand(557), is3h1 = boot.rand(557);
  std::uint64_t is3l2 = boot.rand(557), is3m2 = boot.rand(557), is3h2 = boot.rand(557);

  // build final XSG
  return Xsg512(
    Lfsr<521>(m,  hexGen521), false,
    Lfsr<523>(s0, hexGen523),
    Icg::deriveFromMother(523, as0l1, cs0l1, is0l1), Icg::deriveFromMother(523, as0m1, cs0m1, is0m1), Icg::deriveFromMother(523, as0h1, cs0h1, is0h1),
    Icg::deriveFromMother(523, as0l2, cs0l2, is0l2), Icg::deriveFromMother(523, as0m2, cs0m2, is0m2), Icg::deriveFromMother(523, as0h2, cs0h2, is0h2),
    Icg::deriveFromMother(523, as0l3, cs0l3, is0l3), Icg::deriveFromMother(523, as0m3, cs0m3, is0m3), Icg::deriveFromMother(523, as0h3, cs0h3, is0h3),
    Lfsr<541>(s1, hexGen541),
    Icg::deriveFromMother(541, as1l0, cs1l0, is1l0), Icg::deriveFromMother(541, as1m0, cs1m0, is1m0), Icg::deriveFromMother(541, as1h0, cs1h0, is1h0),
    Icg::deriveFromMother(541, as1l2, cs1l2, is1l2), Icg::deriveFromMother(541, as1m2, cs1m2, is1m2), Icg::deriveFromMother(541, as1h2, cs1h2, is1h2),
    Icg::deriveFromMother(541, as1l3, cs1l3, is1l3), Icg::deriveFromMother(541, as1m3, cs1m3, is1m3), Icg::deriveFromMother(541, as1h3, cs1h3, is1h3),
    Lfsr<547>(s2, hexGen547),
    Icg::deriveFromMother(547, as2l0, cs2l0, is2l0), Icg::deriveFromMother(547, as2m0, cs2m0, is2m0), Icg::deriveFromMother(547, as2h0, cs2h0, is2h0),
    Icg::deriveFromMother(547, as2l1, cs2l1, is2l1), Icg::deriveFromMother(547, as2m1, cs2m1, is2m1), Icg::deriveFromMother(547, as2h1, cs2h1, is2h1),
    Icg::deriveFromMother(547, as2l3, cs2l3, is2l3), Icg::deriveFromMother(547, as2m3, cs2m3, is2m3), Icg::deriveFromMother(547, as2h3, cs2h3, is2h3),
    Lfsr<557>(s3, hexGen557),
    Icg::deriveFromMother(557, as3l0, cs3l0, is3l0), Icg::deriveFromMother(557, as3m0, cs3m0, is3m0), Icg::deriveFromMother(557, as3h0, cs3h0, is3h0),
    Icg::deriveFromMother(557, as3l1, cs3l1, is3l1), Icg::deriveFromMother(557, as3m1, cs3m1, is3m1), Icg::deriveFromMother(557, as3h1, cs3h1, is3h1),
    Icg::deriveFromMother(557, as3l2, cs3l2, is3l2), Icg::deriveFromMother(557, as3m2, cs3m2, is3m2), Icg::deriveFromMother(557, as3h2, cs3h2, is3h2)
  ).blend(4, true);
}


