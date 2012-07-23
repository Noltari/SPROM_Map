/**
	SPROM_Map
	@author: Álvaro Fernández Rojas <noltari@gmail.com>
*/

#include "sprom_map.h"

/*
static void bcma_sprom_extract_r8(struct bcma_bus *bus, const u16 *sprom)
{
	u16 v, o;
	int i;
	u16 pwr_info_offset[] = {
		SSB_SROM8_PWR_INFO_CORE0, SSB_SROM8_PWR_INFO_CORE1,
		SSB_SROM8_PWR_INFO_CORE2, SSB_SROM8_PWR_INFO_CORE3
	};
	BUILD_BUG_ON(ARRAY_SIZE(pwr_info_offset) !=
			ARRAY_SIZE(bus->sprom.core_pwr_info));

	bus->sprom.revision = sprom[SSB_SPROMSIZE_WORDS_R4 - 1] &
		SSB_SPROM_REVISION_REV;

	for (i = 0; i < 3; i++) {
		v = sprom[SPOFF(SSB_SPROM8_IL0MAC) + i];
		*(((__be16 *)bus->sprom.il0mac) + i) = cpu_to_be16(v);
	}

	SPEX(board_rev, SSB_SPROM8_BOARDREV, ~0, 0);

	SPEX(txpid2g[0], SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G0,
	     SSB_SPROM4_TXPID2G0_SHIFT);
	SPEX(txpid2g[1], SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G1,
	     SSB_SPROM4_TXPID2G1_SHIFT);
	SPEX(txpid2g[2], SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G2,
	     SSB_SPROM4_TXPID2G2_SHIFT);
	SPEX(txpid2g[3], SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G3,
	     SSB_SPROM4_TXPID2G3_SHIFT);

	SPEX(txpid5gl[0], SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL0,
	     SSB_SPROM4_TXPID5GL0_SHIFT);
	SPEX(txpid5gl[1], SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL1,
	     SSB_SPROM4_TXPID5GL1_SHIFT);
	SPEX(txpid5gl[2], SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL2,
	     SSB_SPROM4_TXPID5GL2_SHIFT);
	SPEX(txpid5gl[3], SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL3,
	     SSB_SPROM4_TXPID5GL3_SHIFT);

	SPEX(txpid5g[0], SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G0,
	     SSB_SPROM4_TXPID5G0_SHIFT);
	SPEX(txpid5g[1], SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G1,
	     SSB_SPROM4_TXPID5G1_SHIFT);
	SPEX(txpid5g[2], SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G2,
	     SSB_SPROM4_TXPID5G2_SHIFT);
	SPEX(txpid5g[3], SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G3,
	     SSB_SPROM4_TXPID5G3_SHIFT);

	SPEX(txpid5gh[0], SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH0,
	     SSB_SPROM4_TXPID5GH0_SHIFT);
	SPEX(txpid5gh[1], SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH1,
	     SSB_SPROM4_TXPID5GH1_SHIFT);
	SPEX(txpid5gh[2], SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH2,
	     SSB_SPROM4_TXPID5GH2_SHIFT);
	SPEX(txpid5gh[3], SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH3,
	     SSB_SPROM4_TXPID5GH3_SHIFT);

	SPEX(boardflags_lo, SSB_SPROM8_BFLLO, ~0, 0);
	SPEX(boardflags_hi, SSB_SPROM8_BFLHI, ~0, 0);
	SPEX(boardflags2_lo, SSB_SPROM8_BFL2LO, ~0, 0);
	SPEX(boardflags2_hi, SSB_SPROM8_BFL2HI, ~0, 0);

	SPEX(country_code, SSB_SPROM8_CCODE, ~0, 0);

	//Extract cores power info info
	for (i = 0; i < ARRAY_SIZE(pwr_info_offset); i++) {
		o = pwr_info_offset[i];
		SPEX(core_pwr_info[i].itssi_2g, o + SSB_SROM8_2G_MAXP_ITSSI,
			SSB_SPROM8_2G_ITSSI, SSB_SPROM8_2G_ITSSI_SHIFT);
		SPEX(core_pwr_info[i].maxpwr_2g, o + SSB_SROM8_2G_MAXP_ITSSI,
			SSB_SPROM8_2G_MAXP, 0);

		SPEX(core_pwr_info[i].pa_2g[0], o + SSB_SROM8_2G_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_2g[1], o + SSB_SROM8_2G_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_2g[2], o + SSB_SROM8_2G_PA_2, ~0, 0);

		SPEX(core_pwr_info[i].itssi_5g, o + SSB_SROM8_5G_MAXP_ITSSI,
			SSB_SPROM8_5G_ITSSI, SSB_SPROM8_5G_ITSSI_SHIFT);
		SPEX(core_pwr_info[i].maxpwr_5g, o + SSB_SROM8_5G_MAXP_ITSSI,
			SSB_SPROM8_5G_MAXP, 0);
		SPEX(core_pwr_info[i].maxpwr_5gh, o + SSB_SPROM8_5GHL_MAXP,
			SSB_SPROM8_5GH_MAXP, 0);
		SPEX(core_pwr_info[i].maxpwr_5gl, o + SSB_SPROM8_5GHL_MAXP,
			SSB_SPROM8_5GL_MAXP, SSB_SPROM8_5GL_MAXP_SHIFT);

		SPEX(core_pwr_info[i].pa_5gl[0], o + SSB_SROM8_5GL_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gl[1], o + SSB_SROM8_5GL_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gl[2], o + SSB_SROM8_5GL_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[0], o + SSB_SROM8_5G_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[1], o + SSB_SROM8_5G_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[2], o + SSB_SROM8_5G_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[0], o + SSB_SROM8_5GH_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[1], o + SSB_SROM8_5GH_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[2], o + SSB_SROM8_5GH_PA_2, ~0, 0);
	}

	SPEX(fem.ghz2.tssipos, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TSSIPOS,
	     SSB_SROM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz2.extpa_gain, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_EXTPA_GAIN,
	     SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz2.pdet_range, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_PDET_RANGE,
	     SSB_SROM8_FEM_PDET_RANGE_SHIFT);
	SPEX(fem.ghz2.tr_iso, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TR_ISO,
	     SSB_SROM8_FEM_TR_ISO_SHIFT);
	SPEX(fem.ghz2.antswlut, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_ANTSWLUT,
	     SSB_SROM8_FEM_ANTSWLUT_SHIFT);

	SPEX(fem.ghz5.tssipos, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TSSIPOS,
	     SSB_SROM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz5.extpa_gain, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_EXTPA_GAIN,
	     SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz5.pdet_range, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_PDET_RANGE,
	     SSB_SROM8_FEM_PDET_RANGE_SHIFT);
	SPEX(fem.ghz5.tr_iso, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TR_ISO,
	     SSB_SROM8_FEM_TR_ISO_SHIFT);
	SPEX(fem.ghz5.antswlut, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_ANTSWLUT,
	     SSB_SROM8_FEM_ANTSWLUT_SHIFT);
}
*/

/*
	u16 v, o;
	int i;
	u16 pwr_info_offset[] = {
		SSB_SROM8_PWR_INFO_CORE0, SSB_SROM8_PWR_INFO_CORE1,
		SSB_SROM8_PWR_INFO_CORE2, SSB_SROM8_PWR_INFO_CORE3
	};
	BUILD_BUG_ON(ARRAY_SIZE(pwr_info_offset) !=
			ARRAY_SIZE(bus->sprom.core_pwr_info));

	bus->sprom.revision = sprom[SSB_SPROMSIZE_WORDS_R4 - 1] &
		SSB_SPROM_REVISION_REV;

	for (i = 0; i < 3; i++) {
		v = sprom[SPOFF(SSB_SPROM8_IL0MAC) + i];
		*(((__be16 *)bus->sprom.il0mac) + i) = cpu_to_be16(v);
	}

	SPEX(board_rev, SSB_SPROM8_BOARDREV, ~0, 0);

	SPEX(txpid2g[0], SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G0,
	     SSB_SPROM4_TXPID2G0_SHIFT);
	SPEX(txpid2g[1], SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G1,
	     SSB_SPROM4_TXPID2G1_SHIFT);
	SPEX(txpid2g[2], SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G2,
	     SSB_SPROM4_TXPID2G2_SHIFT);
	SPEX(txpid2g[3], SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G3,
	     SSB_SPROM4_TXPID2G3_SHIFT);

	SPEX(txpid5gl[0], SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL0,
	     SSB_SPROM4_TXPID5GL0_SHIFT);
	SPEX(txpid5gl[1], SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL1,
	     SSB_SPROM4_TXPID5GL1_SHIFT);
	SPEX(txpid5gl[2], SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL2,
	     SSB_SPROM4_TXPID5GL2_SHIFT);
	SPEX(txpid5gl[3], SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL3,
	     SSB_SPROM4_TXPID5GL3_SHIFT);

	SPEX(txpid5g[0], SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G0,
	     SSB_SPROM4_TXPID5G0_SHIFT);
	SPEX(txpid5g[1], SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G1,
	     SSB_SPROM4_TXPID5G1_SHIFT);
	SPEX(txpid5g[2], SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G2,
	     SSB_SPROM4_TXPID5G2_SHIFT);
	SPEX(txpid5g[3], SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G3,
	     SSB_SPROM4_TXPID5G3_SHIFT);

	SPEX(txpid5gh[0], SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH0,
	     SSB_SPROM4_TXPID5GH0_SHIFT);
	SPEX(txpid5gh[1], SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH1,
	     SSB_SPROM4_TXPID5GH1_SHIFT);
	SPEX(txpid5gh[2], SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH2,
	     SSB_SPROM4_TXPID5GH2_SHIFT);
	SPEX(txpid5gh[3], SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH3,
	     SSB_SPROM4_TXPID5GH3_SHIFT);

	SPEX(boardflags_lo, SSB_SPROM8_BFLLO, ~0, 0);
	SPEX(boardflags_hi, SSB_SPROM8_BFLHI, ~0, 0);
	SPEX(boardflags2_lo, SSB_SPROM8_BFL2LO, ~0, 0);
	SPEX(boardflags2_hi, SSB_SPROM8_BFL2HI, ~0, 0);

	SPEX(alpha2[0], SSB_SPROM8_CCODE, 0xff00, 8);
	SPEX(alpha2[1], SSB_SPROM8_CCODE, 0x00ff, 0);

	//Extract cores power info info
	for (i = 0; i < ARRAY_SIZE(pwr_info_offset); i++) {
		o = pwr_info_offset[i];
		SPEX(core_pwr_info[i].itssi_2g, o + SSB_SROM8_2G_MAXP_ITSSI,
			SSB_SPROM8_2G_ITSSI, SSB_SPROM8_2G_ITSSI_SHIFT);
		SPEX(core_pwr_info[i].maxpwr_2g, o + SSB_SROM8_2G_MAXP_ITSSI,
			SSB_SPROM8_2G_MAXP, 0);

		SPEX(core_pwr_info[i].pa_2g[0], o + SSB_SROM8_2G_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_2g[1], o + SSB_SROM8_2G_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_2g[2], o + SSB_SROM8_2G_PA_2, ~0, 0);

		SPEX(core_pwr_info[i].itssi_5g, o + SSB_SROM8_5G_MAXP_ITSSI,
			SSB_SPROM8_5G_ITSSI, SSB_SPROM8_5G_ITSSI_SHIFT);
		SPEX(core_pwr_info[i].maxpwr_5g, o + SSB_SROM8_5G_MAXP_ITSSI,
			SSB_SPROM8_5G_MAXP, 0);
		SPEX(core_pwr_info[i].maxpwr_5gh, o + SSB_SPROM8_5GHL_MAXP,
			SSB_SPROM8_5GH_MAXP, 0);
		SPEX(core_pwr_info[i].maxpwr_5gl, o + SSB_SPROM8_5GHL_MAXP,
			SSB_SPROM8_5GL_MAXP, SSB_SPROM8_5GL_MAXP_SHIFT);

		SPEX(core_pwr_info[i].pa_5gl[0], o + SSB_SROM8_5GL_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gl[1], o + SSB_SROM8_5GL_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gl[2], o + SSB_SROM8_5GL_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[0], o + SSB_SROM8_5G_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[1], o + SSB_SROM8_5G_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[2], o + SSB_SROM8_5G_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[0], o + SSB_SROM8_5GH_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[1], o + SSB_SROM8_5GH_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[2], o + SSB_SROM8_5GH_PA_2, ~0, 0);
	}

	SPEX(fem.ghz2.tssipos, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TSSIPOS,
	     SSB_SROM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz2.extpa_gain, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_EXTPA_GAIN,
	     SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz2.pdet_range, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_PDET_RANGE,
	     SSB_SROM8_FEM_PDET_RANGE_SHIFT);
	SPEX(fem.ghz2.tr_iso, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TR_ISO,
	     SSB_SROM8_FEM_TR_ISO_SHIFT);
	SPEX(fem.ghz2.antswlut, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_ANTSWLUT,
	     SSB_SROM8_FEM_ANTSWLUT_SHIFT);

	SPEX(fem.ghz5.tssipos, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TSSIPOS,
	     SSB_SROM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz5.extpa_gain, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_EXTPA_GAIN,
	     SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz5.pdet_range, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_PDET_RANGE,
	     SSB_SROM8_FEM_PDET_RANGE_SHIFT);
	SPEX(fem.ghz5.tr_iso, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TR_ISO,
	     SSB_SROM8_FEM_TR_ISO_SHIFT);
	SPEX(fem.ghz5.antswlut, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_ANTSWLUT,
	     SSB_SROM8_FEM_ANTSWLUT_SHIFT);

	SPEX(ant_available_a, SSB_SPROM8_ANTAVAIL, SSB_SPROM8_ANTAVAIL_A,
	     SSB_SPROM8_ANTAVAIL_A_SHIFT);
	SPEX(ant_available_bg, SSB_SPROM8_ANTAVAIL, SSB_SPROM8_ANTAVAIL_BG,
	     SSB_SPROM8_ANTAVAIL_BG_SHIFT);
	SPEX(maxpwr_bg, SSB_SPROM8_MAXP_BG, SSB_SPROM8_MAXP_BG_MASK, 0);
	SPEX(itssi_bg, SSB_SPROM8_MAXP_BG, SSB_SPROM8_ITSSI_BG,
	     SSB_SPROM8_ITSSI_BG_SHIFT);
	SPEX(maxpwr_a, SSB_SPROM8_MAXP_A, SSB_SPROM8_MAXP_A_MASK, 0);
	SPEX(itssi_a, SSB_SPROM8_MAXP_A, SSB_SPROM8_ITSSI_A,
	     SSB_SPROM8_ITSSI_A_SHIFT);
	SPEX(maxpwr_ah, SSB_SPROM8_MAXP_AHL, SSB_SPROM8_MAXP_AH_MASK, 0);
	SPEX(maxpwr_al, SSB_SPROM8_MAXP_AHL, SSB_SPROM8_MAXP_AL_MASK,
	     SSB_SPROM8_MAXP_AL_SHIFT);
	SPEX(gpio0, SSB_SPROM8_GPIOA, SSB_SPROM8_GPIOA_P0, 0);
	SPEX(gpio1, SSB_SPROM8_GPIOA, SSB_SPROM8_GPIOA_P1,
	     SSB_SPROM8_GPIOA_P1_SHIFT);
	SPEX(gpio2, SSB_SPROM8_GPIOB, SSB_SPROM8_GPIOB_P2, 0);
	SPEX(gpio3, SSB_SPROM8_GPIOB, SSB_SPROM8_GPIOB_P3,
	     SSB_SPROM8_GPIOB_P3_SHIFT);
	SPEX(tri2g, SSB_SPROM8_TRI25G, SSB_SPROM8_TRI2G, 0);
	SPEX(tri5g, SSB_SPROM8_TRI25G, SSB_SPROM8_TRI5G,
	     SSB_SPROM8_TRI5G_SHIFT);
	SPEX(tri5gl, SSB_SPROM8_TRI5GHL, SSB_SPROM8_TRI5GL, 0);
	SPEX(tri5gh, SSB_SPROM8_TRI5GHL, SSB_SPROM8_TRI5GH,
	     SSB_SPROM8_TRI5GH_SHIFT);
	SPEX(rxpo2g, SSB_SPROM8_RXPO, SSB_SPROM8_RXPO2G,
	     SSB_SPROM8_RXPO2G_SHIFT);
	SPEX(rxpo5g, SSB_SPROM8_RXPO, SSB_SPROM8_RXPO5G,
	     SSB_SPROM8_RXPO5G_SHIFT);
	SPEX(rssismf2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISMF2G, 0);
	SPEX(rssismc2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISMC2G,
	     SSB_SPROM8_RSSISMC2G_SHIFT);
	SPEX(rssisav2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISAV2G,
	     SSB_SPROM8_RSSISAV2G_SHIFT);
	SPEX(bxa2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_BXA2G,
	     SSB_SPROM8_BXA2G_SHIFT);
	SPEX(rssismf5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISMF5G, 0);
	SPEX(rssismc5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISMC5G,
	     SSB_SPROM8_RSSISMC5G_SHIFT);
	SPEX(rssisav5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISAV5G,
	     SSB_SPROM8_RSSISAV5G_SHIFT);
	SPEX(bxa5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_BXA5G,
	     SSB_SPROM8_BXA5G_SHIFT);

	SPEX(pa0b0, SSB_SPROM8_PA0B0, ~0, 0);
	SPEX(pa0b1, SSB_SPROM8_PA0B1, ~0, 0);
	SPEX(pa0b2, SSB_SPROM8_PA0B2, ~0, 0);
	SPEX(pa1b0, SSB_SPROM8_PA1B0, ~0, 0);
	SPEX(pa1b1, SSB_SPROM8_PA1B1, ~0, 0);
	SPEX(pa1b2, SSB_SPROM8_PA1B2, ~0, 0);
	SPEX(pa1lob0, SSB_SPROM8_PA1LOB0, ~0, 0);
	SPEX(pa1lob1, SSB_SPROM8_PA1LOB1, ~0, 0);
	SPEX(pa1lob2, SSB_SPROM8_PA1LOB2, ~0, 0);
	SPEX(pa1hib0, SSB_SPROM8_PA1HIB0, ~0, 0);
	SPEX(pa1hib1, SSB_SPROM8_PA1HIB1, ~0, 0);
	SPEX(pa1hib2, SSB_SPROM8_PA1HIB2, ~0, 0);
	SPEX(cck2gpo, SSB_SPROM8_CCK2GPO, ~0, 0);
	SPEX32(ofdm2gpo, SSB_SPROM8_OFDM2GPO, ~0, 0);
	SPEX32(ofdm5glpo, SSB_SPROM8_OFDM5GLPO, ~0, 0);
	SPEX32(ofdm5gpo, SSB_SPROM8_OFDM5GPO, ~0, 0);
	SPEX32(ofdm5ghpo, SSB_SPROM8_OFDM5GHPO, ~0, 0);

	//Extract the antenna gain values.
	SPEX(antenna_gain.a0, SSB_SPROM8_AGAIN01,
	     SSB_SPROM8_AGAIN0, SSB_SPROM8_AGAIN0_SHIFT);
	SPEX(antenna_gain.a1, SSB_SPROM8_AGAIN01,
	     SSB_SPROM8_AGAIN1, SSB_SPROM8_AGAIN1_SHIFT);
	SPEX(antenna_gain.a2, SSB_SPROM8_AGAIN23,
	     SSB_SPROM8_AGAIN2, SSB_SPROM8_AGAIN2_SHIFT);
	SPEX(antenna_gain.a3, SSB_SPROM8_AGAIN23,
	     SSB_SPROM8_AGAIN3, SSB_SPROM8_AGAIN3_SHIFT);

	SPEX(leddc_on_time, SSB_SPROM8_LEDDC, SSB_SPROM8_LEDDC_ON,
	     SSB_SPROM8_LEDDC_ON_SHIFT);
	SPEX(leddc_off_time, SSB_SPROM8_LEDDC, SSB_SPROM8_LEDDC_OFF,
	     SSB_SPROM8_LEDDC_OFF_SHIFT);

	SPEX(txchain, SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_TXCHAIN,
	     SSB_SPROM8_TXRXC_TXCHAIN_SHIFT);
	SPEX(rxchain, SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_RXCHAIN,
	     SSB_SPROM8_TXRXC_RXCHAIN_SHIFT);
	SPEX(antswitch, SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_SWITCH,
	     SSB_SPROM8_TXRXC_SWITCH_SHIFT);

	SPEX(opo, SSB_SPROM8_OFDM2GPO, 0x00ff, 0);

	SPEX_ARRAY8(mcs2gpo, SSB_SPROM8_2G_MCSPO, ~0, 0);
	SPEX_ARRAY8(mcs5gpo, SSB_SPROM8_5G_MCSPO, ~0, 0);
	SPEX_ARRAY8(mcs5glpo, SSB_SPROM8_5GL_MCSPO, ~0, 0);
	SPEX_ARRAY8(mcs5ghpo, SSB_SPROM8_5GH_MCSPO, ~0, 0);

	SPEX(rawtempsense, SSB_SPROM8_RAWTS, SSB_SPROM8_RAWTS_RAWTEMP,
	     SSB_SPROM8_RAWTS_RAWTEMP_SHIFT);
	SPEX(measpower, SSB_SPROM8_RAWTS, SSB_SPROM8_RAWTS_MEASPOWER,
	     SSB_SPROM8_RAWTS_MEASPOWER_SHIFT);
	SPEX(tempsense_slope, SSB_SPROM8_OPT_CORRX,
	     SSB_SPROM8_OPT_CORRX_TEMP_SLOPE,
	     SSB_SPROM8_OPT_CORRX_TEMP_SLOPE_SHIFT);
	SPEX(tempcorrx, SSB_SPROM8_OPT_CORRX, SSB_SPROM8_OPT_CORRX_TEMPCORRX,
	     SSB_SPROM8_OPT_CORRX_TEMPCORRX_SHIFT);
	SPEX(tempsense_option, SSB_SPROM8_OPT_CORRX,
	     SSB_SPROM8_OPT_CORRX_TEMP_OPTION,
	     SSB_SPROM8_OPT_CORRX_TEMP_OPTION_SHIFT);
	SPEX(freqoffset_corr, SSB_SPROM8_HWIQ_IQSWP,
	     SSB_SPROM8_HWIQ_IQSWP_FREQ_CORR,
	     SSB_SPROM8_HWIQ_IQSWP_FREQ_CORR_SHIFT);
	SPEX(iqcal_swp_dis, SSB_SPROM8_HWIQ_IQSWP,
	     SSB_SPROM8_HWIQ_IQSWP_IQCAL_SWP,
	     SSB_SPROM8_HWIQ_IQSWP_IQCAL_SWP_SHIFT);
	SPEX(hw_iqcal_en, SSB_SPROM8_HWIQ_IQSWP, SSB_SPROM8_HWIQ_IQSWP_HW_IQCAL,
	     SSB_SPROM8_HWIQ_IQSWP_HW_IQCAL_SHIFT);

	SPEX(bw40po, SSB_SPROM8_BW40PO, ~0, 0);
	SPEX(cddpo, SSB_SPROM8_CDDPO, ~0, 0);
	SPEX(stbcpo, SSB_SPROM8_STBCPO, ~0, 0);
	SPEX(bwduppo, SSB_SPROM8_BWDUPPO, ~0, 0);

	SPEX(tempthresh, SSB_SPROM8_THERMAL, SSB_SPROM8_THERMAL_TRESH,
	     SSB_SPROM8_THERMAL_TRESH_SHIFT);
	SPEX(tempoffset, SSB_SPROM8_THERMAL, SSB_SPROM8_THERMAL_OFFSET,
	     SSB_SPROM8_THERMAL_OFFSET_SHIFT);
	SPEX(phycal_tempdelta, SSB_SPROM8_TEMPDELTA,
	     SSB_SPROM8_TEMPDELTA_PHYCAL,
	     SSB_SPROM8_TEMPDELTA_PHYCAL_SHIFT);
	SPEX(temps_period, SSB_SPROM8_TEMPDELTA, SSB_SPROM8_TEMPDELTA_PERIOD,
	     SSB_SPROM8_TEMPDELTA_PERIOD_SHIFT);
	SPEX(temps_hysteresis, SSB_SPROM8_TEMPDELTA,
	     SSB_SPROM8_TEMPDELTA_HYSTERESIS,
	     SSB_SPROM8_TEMPDELTA_HYSTERESIS_SHIFT);
*/

int main(int argc, char** argv) {
	//Check arguments.
	if(argc != 3) {
		printf("Usage: %s <file_in> <file_out>\n", argv[0]);
		return -1;
	}

	//Open input/output files.
	int fdin = open(argv[1], O_RDONLY, S_IRWXU | S_IRWXG | S_IRWXO);
	FILE* fdout = fopen(argv[2], "w");

	//Check file descriptor errors.
	if(!fdin) {
		perror("Error creating input file descriptor.\n");
		return -1;
	}
	if(!fdout) {
		perror("Error creating output file descriptor.\n");
		return -1;
	}

	//Check if input file exists and is empty.
	struct stat st;
	if(fstat(fdin, &st) == -1) {
		perror("[ERROR] Input file doesn't exist.\n");
		return -1;
	}
	long fdin_size = st.st_size;
	if(fdin_size == 0) {
		perror("[ERROR] Input file is empty.\n");
		return -1;
	}

	//Call main function.
	return sprom_map(fdin, fdin_size, fdout);
}

int sprom_map(int fdin, long fdin_size, FILE* fdout) {
	uint16_t sprom[fdin_size / 2];
	ssize_t bytes_read = read(fdin, &sprom, fdin_size);
	if(bytes_read != fdin_size) {
		printf("Input file error.\n");
		return -1;
	}

	int i;
	for(i = 0; i < fdin_size / 2; i++) {
		sprom[i] = ntohs(sprom[i]);
	}

	//Header
	fprintf(fdout, "static struct ssb_sprom bcm63xx_sprom = {\n");

	//Params
	uint8_t revision = sprom[SSB_SPROMSIZE_WORDS_R4 - 1] & SSB_SPROM_REVISION_REV;
		fprintf(fdout, "\t.revision\t\t\t\t\t\t= 0x%x,\n", revision);
	uint16_t board_rev = SPEX(SSB_SPROM8_BOARDREV, ~0, 0);
		fprintf(fdout, "\t.board_rev\t\t\t\t\t\t= 0x%x,\n", board_rev);
	uint8_t txpid2g[4];
		txpid2g[0] = SPEX(SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G0, SSB_SPROM4_TXPID2G0_SHIFT);
		txpid2g[1] = SPEX(SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G1, SSB_SPROM4_TXPID2G1_SHIFT);
		txpid2g[2] = SPEX(SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G2, SSB_SPROM4_TXPID2G2_SHIFT);
		txpid2g[3] = SPEX(SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G3, SSB_SPROM4_TXPID2G3_SHIFT);
		fprintf(fdout, "\t.txpid2g\t\t\t\t\t\t= {0x%x,0x%x,0x%x,0x%x},\n", txpid2g[0], txpid2g[1], txpid2g[2], txpid2g[3]);
	uint8_t txpid5gl[4];
		txpid5gl[0] = SPEX(SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL0, SSB_SPROM4_TXPID5GL0_SHIFT);
		txpid5gl[1] = SPEX(SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL1, SSB_SPROM4_TXPID5GL1_SHIFT);
		txpid5gl[2] = SPEX(SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL2, SSB_SPROM4_TXPID5GL2_SHIFT);
		txpid5gl[3] = SPEX(SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL3, SSB_SPROM4_TXPID5GL3_SHIFT);
		fprintf(fdout, "\t.txpid5gl\t\t\t\t\t\t= {0x%x,0x%x,0x%x,0x%x},\n", txpid5gl[0], txpid5gl[1], txpid5gl[2], txpid5gl[3]);
	uint8_t txpid5g[4];
		txpid5g[0] = SPEX(SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G0, SSB_SPROM4_TXPID5G0_SHIFT);
		txpid5g[1] = SPEX(SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G1, SSB_SPROM4_TXPID5G1_SHIFT);
		txpid5g[2] = SPEX(SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G2, SSB_SPROM4_TXPID5G2_SHIFT);
		txpid5g[3] = SPEX(SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G3, SSB_SPROM4_TXPID5G3_SHIFT);
		fprintf(fdout, "\t.txpid5g\t\t\t\t\t\t= {0x%x,0x%x,0x%x,0x%x},\n", txpid5g[0], txpid5g[1], txpid5g[2], txpid5g[3]);
	uint8_t txpid5gh[4];
		txpid5gh[0] = SPEX(SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH0, SSB_SPROM4_TXPID5GH0_SHIFT);
		txpid5gh[1] = SPEX(SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH1, SSB_SPROM4_TXPID5GH1_SHIFT);
		txpid5gh[2] = SPEX(SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH2, SSB_SPROM4_TXPID5GH2_SHIFT);
		txpid5gh[3] = SPEX(SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH3, SSB_SPROM4_TXPID5GH3_SHIFT);
		fprintf(fdout, "\t.txpid5gh\t\t\t\t\t\t= {0x%x,0x%x,0x%x,0x%x},\n", txpid5gh[0], txpid5gh[1], txpid5gh[2], txpid5gh[3]);
	uint16_t boardflags_lo = SPEX(SSB_SPROM8_BFLLO, ~0, 0);
		fprintf(fdout, "\t.boardflags_lo\t\t\t\t\t= 0x%x,\n", boardflags_lo);
	uint16_t boardflags_hi = SPEX(SSB_SPROM8_BFLHI, ~0, 0);
		fprintf(fdout, "\t.boardflags_hi\t\t\t\t\t= 0x%x,\n", boardflags_hi);
	uint16_t boardflags2_lo = SPEX(SSB_SPROM8_BFL2LO, ~0, 0);
		fprintf(fdout, "\t.boardflags2_lo\t\t\t\t\t= 0x%x,\n", boardflags2_lo);
	uint16_t boardflags2_hi = SPEX(SSB_SPROM8_BFL2HI, ~0, 0);
		fprintf(fdout, "\t.boardflags2_hi\t\t\t\t\t= 0x%x,\n", boardflags2_hi);
	/*
	uint8_t country_code = SPEX(SSB_SPROM8_CCODE, ~0, 0);
		fprintf(fdout, "\t.country_code\t\t\t= 0x%x,\n", country_code);
	*/
	char alpha2[2];
		alpha2[0] = SPEX(SSB_SPROM8_CCODE, 0xff00, 8);
		alpha2[1] = SPEX(SSB_SPROM8_CCODE, 0x00ff, 0);
		fprintf(fdout, "\t.alpha2[0]\t\t\t\t\t\t= 0x%x,\n", alpha2[0]);
		fprintf(fdout, "\t.alpha2[1]\t\t\t\t\t\t= 0x%x,\n", alpha2[1]);

	uint16_t pwr_info_offset[] = {
		SSB_SROM8_PWR_INFO_CORE0, SSB_SROM8_PWR_INFO_CORE1,
		SSB_SROM8_PWR_INFO_CORE2, SSB_SROM8_PWR_INFO_CORE3
	};
	uint16_t o;
	for (i = 0; i < 4; i++) {
		o = pwr_info_offset[i];

		uint8_t itssi_2g = SPEX(o + SSB_SROM8_2G_MAXP_ITSSI, SSB_SPROM8_2G_ITSSI, SSB_SPROM8_2G_ITSSI_SHIFT);
			fprintf(fdout, "\t.core_pwr_info[%d].itssi_2g\t\t= 0x%x,\n", i, itssi_2g);
		uint8_t maxpwr_2g = SPEX(o + SSB_SROM8_2G_MAXP_ITSSI, SSB_SPROM8_2G_MAXP, 0);
			fprintf(fdout, "\t.core_pwr_info[%d].maxpwr_2g\t\t= 0x%x,\n", i, maxpwr_2g);
		uint16_t pa_2g[4];
			pa_2g[0] = SPEX(o + SSB_SROM8_2G_PA_0, ~0, 0);
			pa_2g[1] = SPEX(o + SSB_SROM8_2G_PA_1, ~0, 0);
			pa_2g[2] = SPEX(o + SSB_SROM8_2G_PA_2, ~0, 0);
			pa_2g[3] = 0xffff;
			fprintf(fdout, "\t.core_pwr_info[%d].pa_2g\t\t\t= {0x%x,0x%x,0x%x,0x%x},\n", i, pa_2g[0], pa_2g[1], pa_2g[2], pa_2g[3]);
		uint8_t itssi_5g = SPEX(o + SSB_SROM8_5G_MAXP_ITSSI, SSB_SPROM8_5G_ITSSI, SSB_SPROM8_5G_ITSSI_SHIFT);
			fprintf(fdout, "\t.core_pwr_info[%d].itssi_5g\t\t= 0x%x,\n", i, itssi_5g);
		uint8_t maxpwr_5g = SPEX(o + SSB_SROM8_5G_MAXP_ITSSI, SSB_SPROM8_5G_MAXP, 0);
			fprintf(fdout, "\t.core_pwr_info[%d].maxpwr_5g\t\t= 0x%x,\n", i, maxpwr_5g);
		uint8_t maxpwr_5gh = SPEX(o + SSB_SPROM8_5GHL_MAXP, SSB_SPROM8_5GH_MAXP, 0);
			fprintf(fdout, "\t.core_pwr_info[%d].maxpwr_5gh\t= 0x%x,\n", i, maxpwr_5gh);
		uint8_t maxpwr_5gl = SPEX(o + SSB_SPROM8_5GHL_MAXP, SSB_SPROM8_5GL_MAXP, SSB_SPROM8_5GL_MAXP_SHIFT);
			fprintf(fdout, "\t.core_pwr_info[%d].maxpwr_5gl\t= 0x%x,\n", i, maxpwr_5gl);
		uint16_t pa_5gl[4];
			pa_5gl[0] = SPEX(o + SSB_SROM8_5GL_PA_0, ~0, 0);
			pa_5gl[1] = SPEX(o + SSB_SROM8_5GL_PA_1, ~0, 0);
			pa_5gl[2] = SPEX(o + SSB_SROM8_5GL_PA_2, ~0, 0);
			pa_5gl[3] = 0xffff;
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5gl\t\t= {0x%x,0x%x,0x%x,0x%x},\n", i, pa_5gl[0], pa_5gl[1], pa_5gl[2], pa_5gl[3]);
		uint16_t pa_5g[4];
			pa_5g[0] = SPEX(o + SSB_SROM8_5G_PA_0, ~0, 0);
			pa_5g[1] = SPEX(o + SSB_SROM8_5G_PA_1, ~0, 0);
			pa_5g[2] = SPEX(o + SSB_SROM8_5G_PA_2, ~0, 0);
			pa_5g[3] = 0xffff;
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5g\t\t\t= {0x%x,0x%x,0x%x,0x%x},\n", i, pa_5g[0], pa_5g[1], pa_5g[2], pa_5g[3]);
		uint16_t pa_5gh[4];
			pa_5gh[0] = SPEX(o + SSB_SROM8_5GH_PA_0, ~0, 0);
			pa_5gh[1] = SPEX(o + SSB_SROM8_5GH_PA_1, ~0, 0);
			pa_5gh[2] = SPEX(o + SSB_SROM8_5GH_PA_2, ~0, 0);
			pa_5gh[3] = 0xffff;
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5gh\t\t= {0x%x,0x%x,0x%x,0x%x},\n", i, pa_5gh[0], pa_5gh[1], pa_5gh[2], pa_5gh[3]);
	}

	uint8_t tssipos_2g = SPEX(SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TSSIPOS, SSB_SROM8_FEM_TSSIPOS_SHIFT);
		fprintf(fdout, "\t.fem.ghz2.tssipos\t\t\t\t= 0x%x,\n", tssipos_2g);
	uint8_t extpa_gain_2g = SPEX(SSB_SPROM8_FEM2G, SSB_SROM8_FEM_EXTPA_GAIN, SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
		fprintf(fdout, "\t.fem.ghz2.extpa_gain\t\t\t= 0x%x,\n", extpa_gain_2g);
	uint8_t pdet_range_2g = SPEX(SSB_SPROM8_FEM2G, SSB_SROM8_FEM_PDET_RANGE, SSB_SROM8_FEM_PDET_RANGE_SHIFT);
		fprintf(fdout, "\t.fem.ghz2.pdet_range\t\t\t= 0x%x,\n", pdet_range_2g);
	uint8_t tr_iso_2g = SPEX(SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TR_ISO, SSB_SROM8_FEM_TR_ISO_SHIFT);
		fprintf(fdout, "\t.fem.ghz2.tr_iso\t\t\t\t= 0x%x,\n", tr_iso_2g);
	uint8_t antswlut_2g = SPEX(SSB_SPROM8_FEM2G, SSB_SROM8_FEM_ANTSWLUT, SSB_SROM8_FEM_ANTSWLUT_SHIFT);
		fprintf(fdout, "\t.fem.ghz2.antswlut\t\t\t\t= 0x%x,\n", antswlut_2g);
	uint8_t tssipos_5g = SPEX(SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TSSIPOS, SSB_SROM8_FEM_TSSIPOS_SHIFT);
		fprintf(fdout, "\t.fem.ghz5.tssipos\t\t\t\t= 0x%x,\n", tssipos_5g);
	uint8_t extpa_gain_5g = SPEX(SSB_SPROM8_FEM5G, SSB_SROM8_FEM_EXTPA_GAIN, SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
		fprintf(fdout, "\t.fem.ghz5.extpa_gain\t\t\t= 0x%x,\n", extpa_gain_5g);
	uint8_t pdet_range_5g = SPEX(SSB_SPROM8_FEM5G, SSB_SROM8_FEM_PDET_RANGE, SSB_SROM8_FEM_PDET_RANGE_SHIFT);
		fprintf(fdout, "\t.fem.ghz5.pdet_range\t\t\t= 0x%x,\n", pdet_range_5g);
	uint8_t tr_iso_5g = SPEX(SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TR_ISO, SSB_SROM8_FEM_TR_ISO_SHIFT);
		fprintf(fdout, "\t.fem.ghz5.tr_iso\t\t\t\t= 0x%x,\n", tr_iso_5g);
	uint8_t antswlut_5g = SPEX(SSB_SPROM8_FEM5G, SSB_SROM8_FEM_ANTSWLUT, SSB_SROM8_FEM_ANTSWLUT_SHIFT);
		fprintf(fdout, "\t.fem.ghz5.antswlut\t\t\t\t= 0x%x,\n", antswlut_5g);

	/*
		Openwrt extra
	*/

	uint8_t ant_available_a = SPEX(SSB_SPROM8_ANTAVAIL, SSB_SPROM8_ANTAVAIL_A, SSB_SPROM8_ANTAVAIL_A_SHIFT);
		fprintf(fdout, "\t.ant_available_a\t\t\t\t= 0x%x,\n", ant_available_a);
	uint8_t ant_available_bg = SPEX(SSB_SPROM8_ANTAVAIL, SSB_SPROM8_ANTAVAIL_BG, SSB_SPROM8_ANTAVAIL_BG_SHIFT);
		fprintf(fdout, "\t.ant_available_bg\t\t\t\t= 0x%x,\n", ant_available_bg);
	uint8_t maxpwr_bg = SPEX(SSB_SPROM8_MAXP_BG, SSB_SPROM8_MAXP_BG_MASK, 0);
		fprintf(fdout, "\t.maxpwr_bg\t\t\t\t\t\t= 0x%x,\n", maxpwr_bg);
	uint8_t itssi_bg = SPEX(SSB_SPROM8_MAXP_BG, SSB_SPROM8_ITSSI_BG, SSB_SPROM8_ITSSI_BG_SHIFT);
		fprintf(fdout, "\t.itssi_bg\t\t\t\t\t\t= 0x%x,\n", itssi_bg);
	uint8_t maxpwr_a = SPEX(SSB_SPROM8_MAXP_A, SSB_SPROM8_MAXP_A_MASK, 0);
		fprintf(fdout, "\t.maxpwr_a\t\t\t\t\t\t= 0x%x,\n", maxpwr_a);
	uint8_t itssi_a = SPEX(SSB_SPROM8_MAXP_A, SSB_SPROM8_ITSSI_A, SSB_SPROM8_ITSSI_A_SHIFT);
		fprintf(fdout, "\t.itssi_a\t\t\t\t\t\t= 0x%x,\n", itssi_a);
	uint8_t maxpwr_ah = SPEX(SSB_SPROM8_MAXP_AHL, SSB_SPROM8_MAXP_AH_MASK, 0);
		fprintf(fdout, "\t.maxpwr_ah\t\t\t\t\t\t= 0x%x,\n", maxpwr_ah);
	uint8_t maxpwr_al = SPEX(SSB_SPROM8_MAXP_AHL, SSB_SPROM8_MAXP_AL_MASK, SSB_SPROM8_MAXP_AL_SHIFT);
		fprintf(fdout, "\t.maxpwr_al\t\t\t\t\t\t= 0x%x,\n", maxpwr_al);
	uint8_t gpio0 = SPEX(SSB_SPROM8_GPIOA, SSB_SPROM8_GPIOA_P0, 0);
		fprintf(fdout, "\t.gpio0\t\t\t\t\t\t\t= 0x%x,\n", gpio0);
	uint8_t gpio1 = SPEX(SSB_SPROM8_GPIOA, SSB_SPROM8_GPIOA_P1, SSB_SPROM8_GPIOA_P1_SHIFT);
		fprintf(fdout, "\t.gpio1\t\t\t\t\t\t\t= 0x%x,\n", gpio1);
	uint8_t gpio2 = SPEX(SSB_SPROM8_GPIOB, SSB_SPROM8_GPIOB_P2, 0);
		fprintf(fdout, "\t.gpio2\t\t\t\t\t\t\t= 0x%x,\n", gpio2);
	uint8_t gpio3 = SPEX(SSB_SPROM8_GPIOB, SSB_SPROM8_GPIOB_P3, SSB_SPROM8_GPIOB_P3_SHIFT);
		fprintf(fdout, "\t.gpio3\t\t\t\t\t\t\t= 0x%x,\n", gpio3);
	uint8_t tri2g = SPEX(SSB_SPROM8_TRI25G, SSB_SPROM8_TRI2G, 0);
		fprintf(fdout, "\t.tri2g\t\t\t\t\t\t\t= 0x%x,\n", tri2g);
	uint8_t tri5g = SPEX(SSB_SPROM8_TRI25G, SSB_SPROM8_TRI5G, SSB_SPROM8_TRI5G_SHIFT);
		fprintf(fdout, "\t.tri5g\t\t\t\t\t\t\t= 0x%x,\n", tri5g);
	uint8_t tri5gl = SPEX(SSB_SPROM8_TRI5GHL, SSB_SPROM8_TRI5GL, 0);
		fprintf(fdout, "\t.tri5gl\t\t\t\t\t\t\t= 0x%x,\n", tri5gl);
	uint8_t tri5gh = SPEX(SSB_SPROM8_TRI5GHL, SSB_SPROM8_TRI5GH, SSB_SPROM8_TRI5GH_SHIFT);
		fprintf(fdout, "\t.tri5gh\t\t\t\t\t\t\t= 0x%x,\n", tri5gh);
	uint8_t rxpo2g = SPEX(SSB_SPROM8_RXPO, SSB_SPROM8_RXPO2G, SSB_SPROM8_RXPO2G_SHIFT);
		fprintf(fdout, "\t.rxpo2g\t\t\t\t\t\t\t= 0x%x,\n", rxpo2g);
	uint8_t rxpo5g = SPEX(SSB_SPROM8_RXPO, SSB_SPROM8_RXPO5G, SSB_SPROM8_RXPO5G_SHIFT);
		fprintf(fdout, "\t.rxpo5g\t\t\t\t\t\t\t= 0x%x,\n", rxpo5g);
	uint8_t rssismf2g = SPEX(SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISMF2G, 0);
		fprintf(fdout, "\t.rssismf2g\t\t\t\t\t\t= 0x%x,\n", rssismf2g);
	uint8_t rssismc2g = SPEX(SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISMC2G, SSB_SPROM8_RSSISMC2G_SHIFT);
		fprintf(fdout, "\t.rssismc2g\t\t\t\t\t\t= 0x%x,\n", rssismc2g);
	uint8_t rssisav2g = SPEX(SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISAV2G, SSB_SPROM8_RSSISAV2G_SHIFT);
		fprintf(fdout, "\t.rssisav2g\t\t\t\t\t\t= 0x%x,\n", rssisav2g);
	uint8_t bxa2g = SPEX(SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_BXA2G, SSB_SPROM8_BXA2G_SHIFT);
		fprintf(fdout, "\t.bxa2g\t\t\t\t\t\t\t= 0x%x,\n", bxa2g);
	uint8_t rssismf5g = SPEX(SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISMF5G, 0);
		fprintf(fdout, "\t.rssismf5g\t\t\t\t\t\t= 0x%x,\n", rssismf5g);
	uint8_t rssismc5g = SPEX(SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISMC5G, SSB_SPROM8_RSSISMC5G_SHIFT);
		fprintf(fdout, "\t.rssismc5g\t\t\t\t\t\t= 0x%x,\n", rssismc5g);
	uint8_t rssisav5g = SPEX(SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISAV5G, SSB_SPROM8_RSSISAV5G_SHIFT);
		fprintf(fdout, "\t.rssisav5g\t\t\t\t\t\t= 0x%x,\n", rssisav5g);
	uint8_t bxa5g = SPEX(SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_BXA5G, SSB_SPROM8_BXA5G_SHIFT);
		fprintf(fdout, "\t.bxa5g\t\t\t\t\t\t\t= 0x%x,\n", bxa5g);

	uint16_t pa0b0 = SPEX(SSB_SPROM8_PA0B0, ~0, 0);
		fprintf(fdout, "\t.pa0b0\t\t\t\t\t\t\t= 0x%x,\n", pa0b0);
	uint16_t pa0b1 = SPEX(SSB_SPROM8_PA0B1, ~0, 0);
		fprintf(fdout, "\t.pa0b1\t\t\t\t\t\t\t= 0x%x,\n", pa0b1);
	uint16_t pa0b2 = SPEX(SSB_SPROM8_PA0B2, ~0, 0);
		fprintf(fdout, "\t.pa0b2\t\t\t\t\t\t\t= 0x%x,\n", pa0b2);
	uint16_t pa1b0 = SPEX(SSB_SPROM8_PA1B0, ~0, 0);
		fprintf(fdout, "\t.pa1b0\t\t\t\t\t\t\t= 0x%x,\n", pa1b0);
	uint16_t pa1b1 = SPEX(SSB_SPROM8_PA1B1, ~0, 0);
		fprintf(fdout, "\t.pa1b1\t\t\t\t\t\t\t= 0x%x,\n", pa1b1);
	uint16_t pa1b2 = SPEX(SSB_SPROM8_PA1B2, ~0, 0);
		fprintf(fdout, "\t.pa1b2\t\t\t\t\t\t\t= 0x%x,\n", pa1b2);
	uint16_t pa1lob0 = SPEX(SSB_SPROM8_PA1LOB0, ~0, 0);
		fprintf(fdout, "\t.pa1lob0\t\t\t\t\t\t= 0x%x,\n", pa1lob0);
	uint16_t pa1lob1 = SPEX(SSB_SPROM8_PA1LOB1, ~0, 0);
		fprintf(fdout, "\t.pa1lob1\t\t\t\t\t\t= 0x%x,\n", pa1lob1);
	uint16_t pa1lob2 = SPEX(SSB_SPROM8_PA1LOB2, ~0, 0);
		fprintf(fdout, "\t.pa1lob2\t\t\t\t\t\t= 0x%x,\n", pa1lob2);
	uint16_t pa1hib0 = SPEX(SSB_SPROM8_PA1HIB0, ~0, 0);
		fprintf(fdout, "\t.pa1hib0\t\t\t\t\t\t= 0x%x,\n", pa1hib0);
	uint16_t pa1hib1 = SPEX(SSB_SPROM8_PA1HIB1, ~0, 0);
		fprintf(fdout, "\t.pa1hib1\t\t\t\t\t\t= 0x%x,\n", pa1hib1);
	uint16_t pa1hib2 = SPEX(SSB_SPROM8_PA1HIB2, ~0, 0);
		fprintf(fdout, "\t.pa1hib2\t\t\t\t\t\t= 0x%x,\n", pa1hib2);
	uint16_t cck2gpo = SPEX(SSB_SPROM8_CCK2GPO, ~0, 0);
		fprintf(fdout, "\t.cck2gpo\t\t\t\t\t\t= 0x%x,\n", cck2gpo);
	uint32_t ofdm2gpo = SPEX(SSB_SPROM8_OFDM2GPO, ~0, 0);
		fprintf(fdout, "\t.ofdm2gpo\t\t\t\t\t\t= 0x%x,\n", ofdm2gpo);
	uint32_t ofdm5glpo = SPEX(SSB_SPROM8_OFDM5GLPO, ~0, 0);
		fprintf(fdout, "\t.ofdm5glpo\t\t\t\t\t\t= 0x%x,\n", ofdm5glpo);
	uint32_t ofdm5gpo = SPEX(SSB_SPROM8_OFDM5GPO, ~0, 0);
		fprintf(fdout, "\t.ofdm5gpo\t\t\t\t\t\t= 0x%x,\n", ofdm5gpo);
	uint32_t ofdm5ghpo = SPEX(SSB_SPROM8_OFDM5GHPO, ~0, 0);
		fprintf(fdout, "\t.ofdm5ghpo\t\t\t\t\t\t= 0x%x,\n", ofdm5ghpo);

	uint8_t antenna_gain_a0 = SPEX(SSB_SPROM8_AGAIN01, SSB_SPROM8_AGAIN0, SSB_SPROM8_AGAIN0_SHIFT);
		fprintf(fdout, "\t.antenna_gain.a0\t\t\t\t= 0x%x,\n", antenna_gain_a0);
	uint8_t antenna_gain_a1 = SPEX(SSB_SPROM8_AGAIN01, SSB_SPROM8_AGAIN1, SSB_SPROM8_AGAIN1_SHIFT);
		fprintf(fdout, "\t.antenna_gain.a1\t\t\t\t= 0x%x,\n", antenna_gain_a1);
	uint8_t antenna_gain_a2 = SPEX(SSB_SPROM8_AGAIN23, SSB_SPROM8_AGAIN2, SSB_SPROM8_AGAIN2_SHIFT);
		fprintf(fdout, "\t.antenna_gain.a2\t\t\t\t= 0x%x,\n", antenna_gain_a2);
	uint8_t antenna_gain_a3 = SPEX(SSB_SPROM8_AGAIN23, SSB_SPROM8_AGAIN3, SSB_SPROM8_AGAIN3_SHIFT);
		fprintf(fdout, "\t.antenna_gain.a3\t\t\t\t= 0x%x,\n", antenna_gain_a3);

	uint8_t leddc_on_time = SPEX(SSB_SPROM8_LEDDC, SSB_SPROM8_LEDDC_ON, SSB_SPROM8_LEDDC_ON_SHIFT);
		fprintf(fdout, "\t.leddc_on_time\t\t\t\t\t= 0x%x,\n", leddc_on_time);
	uint8_t leddc_off_time = SPEX(SSB_SPROM8_LEDDC, SSB_SPROM8_LEDDC_OFF, SSB_SPROM8_LEDDC_OFF_SHIFT);
		fprintf(fdout, "\t.leddc_off_time\t\t\t\t\t= 0x%x,\n", leddc_off_time);

	uint8_t txchain = SPEX(SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_TXCHAIN, SSB_SPROM8_TXRXC_TXCHAIN_SHIFT);
		fprintf(fdout, "\t.txchain\t\t\t\t\t\t= 0x%x,\n", txchain);
	uint8_t rxchain = SPEX(SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_RXCHAIN, SSB_SPROM8_TXRXC_RXCHAIN_SHIFT);
		fprintf(fdout, "\t.rxchain\t\t\t\t\t\t= 0x%x,\n", rxchain);
	uint8_t antswitch = SPEX(SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_SWITCH, SSB_SPROM8_TXRXC_SWITCH_SHIFT);
		fprintf(fdout, "\t.antswitch\t\t\t\t\t\t= 0x%x,\n", antswitch);

	uint8_t opo = SPEX(SSB_SPROM8_OFDM2GPO, 0x00ff, 0);
		fprintf(fdout, "\t.opo\t\t\t\t\t\t\t= 0x%x,\n", opo);

	uint16_t mcs2gpo[8];
	uint16_t mcs5gpo[8];
	uint16_t mcs5glpo[8];
	uint16_t mcs5ghpo[8];
		for(i = 0; i < 8; i++) {
			mcs2gpo[i] = SPEX(SSB_SPROM8_2G_MCSPO + (i * 2), ~0, 0);
			mcs5gpo[i] = SPEX(SSB_SPROM8_5G_MCSPO + (i * 2), ~0, 0);
			mcs5glpo[i] = SPEX(SSB_SPROM8_5GL_MCSPO + (i * 2), ~0, 0);
			mcs5ghpo[i] = SPEX(SSB_SPROM8_5GH_MCSPO + (i * 2), ~0, 0);
		}
		fprintf(fdout, "\t.mcs2gpo\t\t\t\t\t\t= {0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x},\n", mcs2gpo[0], mcs2gpo[1], mcs2gpo[2], mcs2gpo[3], mcs2gpo[4], mcs2gpo[5], mcs2gpo[6], mcs2gpo[7]);
		fprintf(fdout, "\t.mcs5gpo\t\t\t\t\t\t= {0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x},\n", mcs5gpo[0], mcs5gpo[1], mcs5gpo[2], mcs5gpo[3], mcs5gpo[4], mcs5gpo[5], mcs5gpo[6], mcs5gpo[7]);
		fprintf(fdout, "\t.mcs5glpo\t\t\t\t\t\t= {0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x},\n", mcs5glpo[0], mcs5glpo[1], mcs5glpo[2], mcs5glpo[3], mcs5glpo[4], mcs5glpo[5], mcs5glpo[6], mcs5glpo[7]);
		fprintf(fdout, "\t.mcs5ghpo\t\t\t\t\t\t= {0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x},\n", mcs5ghpo[0], mcs5ghpo[1], mcs5ghpo[2], mcs5ghpo[3], mcs5ghpo[4], mcs5ghpo[5], mcs5ghpo[6], mcs5ghpo[7]);

	uint16_t rawtempsense = SPEX(SSB_SPROM8_RAWTS, SSB_SPROM8_RAWTS_RAWTEMP, SSB_SPROM8_RAWTS_RAWTEMP_SHIFT);
		fprintf(fdout, "\t.rawtempsense\t\t\t\t\t= 0x%x,\n", rawtempsense);
	uint8_t measpower = SPEX(SSB_SPROM8_RAWTS, SSB_SPROM8_RAWTS_MEASPOWER, SSB_SPROM8_RAWTS_MEASPOWER_SHIFT);
		fprintf(fdout, "\t.measpower\t\t\t\t\t\t= 0x%x,\n", measpower);
	uint8_t tempsense_slope = SPEX(SSB_SPROM8_OPT_CORRX, SSB_SPROM8_OPT_CORRX_TEMP_SLOPE, SSB_SPROM8_OPT_CORRX_TEMP_SLOPE_SHIFT);
		fprintf(fdout, "\t.tempsense_slope\t\t\t\t= 0x%x,\n", tempsense_slope);
	uint8_t tempcorrx = SPEX(SSB_SPROM8_OPT_CORRX, SSB_SPROM8_OPT_CORRX_TEMPCORRX, SSB_SPROM8_OPT_CORRX_TEMPCORRX_SHIFT);
		fprintf(fdout, "\t.tempcorrx\t\t\t\t\t\t= 0x%x,\n", tempcorrx);
	uint8_t tempsense_option = SPEX(SSB_SPROM8_OPT_CORRX, SSB_SPROM8_OPT_CORRX_TEMP_OPTION, SSB_SPROM8_OPT_CORRX_TEMP_OPTION_SHIFT);
		fprintf(fdout, "\t.tempsense_option\t\t\t\t= 0x%x,\n", tempsense_option);
	uint8_t freqoffset_corr = SPEX(SSB_SPROM8_HWIQ_IQSWP, SSB_SPROM8_HWIQ_IQSWP_FREQ_CORR, SSB_SPROM8_HWIQ_IQSWP_FREQ_CORR_SHIFT);
		fprintf(fdout, "\t.freqoffset_corr\t\t\t\t= 0x%x,\n", freqoffset_corr);
	uint8_t iqcal_swp_dis = SPEX(SSB_SPROM8_HWIQ_IQSWP, SSB_SPROM8_HWIQ_IQSWP_IQCAL_SWP, SSB_SPROM8_HWIQ_IQSWP_IQCAL_SWP_SHIFT);
		fprintf(fdout, "\t.iqcal_swp_dis\t\t\t\t\t= 0x%x,\n", iqcal_swp_dis);
	uint8_t hw_iqcal_en = SPEX(SSB_SPROM8_HWIQ_IQSWP, SSB_SPROM8_HWIQ_IQSWP_HW_IQCAL, SSB_SPROM8_HWIQ_IQSWP_HW_IQCAL_SHIFT);
		fprintf(fdout, "\t.hw_iqcal_en\t\t\t\t\t= 0x%x,\n", hw_iqcal_en);

	uint16_t bw40po = SPEX(SSB_SPROM8_BW40PO, ~0, 0);
		fprintf(fdout, "\t.bw40po\t\t\t\t\t\t\t= 0x%x,\n", bw40po);
	uint16_t cddpo = SPEX(SSB_SPROM8_CDDPO, ~0, 0);
		fprintf(fdout, "\t.cddpo\t\t\t\t\t\t\t= 0x%x,\n", cddpo);
	uint16_t stbcpo = SPEX(SSB_SPROM8_STBCPO, ~0, 0);
		fprintf(fdout, "\t.stbcpo\t\t\t\t\t\t\t= 0x%x,\n", stbcpo);
	uint16_t bwduppo = SPEX(SSB_SPROM8_BWDUPPO, ~0, 0);
		fprintf(fdout, "\t.bwduppo\t\t\t\t\t\t= 0x%x,\n", bwduppo);

	uint8_t tempthresh = SPEX(SSB_SPROM8_THERMAL, SSB_SPROM8_THERMAL_TRESH, SSB_SPROM8_THERMAL_TRESH_SHIFT);
		fprintf(fdout, "\t.tempthresh\t\t\t\t\t\t= 0x%x,\n", tempthresh);
	uint8_t tempoffset = SPEX(SSB_SPROM8_THERMAL, SSB_SPROM8_THERMAL_OFFSET, SSB_SPROM8_THERMAL_OFFSET_SHIFT);
		fprintf(fdout, "\t.tempoffset\t\t\t\t\t\t= 0x%x,\n", tempoffset);
	uint8_t phycal_tempdelta = SPEX(SSB_SPROM8_TEMPDELTA, SSB_SPROM8_TEMPDELTA_PHYCAL, SSB_SPROM8_TEMPDELTA_PHYCAL_SHIFT);
		fprintf(fdout, "\t.phycal_tempdelta\t\t\t\t= 0x%x,\n", phycal_tempdelta);
	uint8_t temps_period = SPEX(SSB_SPROM8_TEMPDELTA, SSB_SPROM8_TEMPDELTA_PERIOD, SSB_SPROM8_TEMPDELTA_PERIOD_SHIFT);
		fprintf(fdout, "\t.temps_period\t\t\t\t\t= 0x%x,\n", temps_period);
	uint8_t temps_hysteresis = SPEX(SSB_SPROM8_TEMPDELTA, SSB_SPROM8_TEMPDELTA_HYSTERESIS, SSB_SPROM8_TEMPDELTA_HYSTERESIS_SHIFT);
		fprintf(fdout, "\t.temps_hysteresis\t\t\t\t= 0x%x,\n", temps_hysteresis);

	//Footer
	fprintf(fdout, "};\n");

	close(fdin);
	fclose(fdout);

	return 0;
}
