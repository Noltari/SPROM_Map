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
		fprintf(fdout, "\t.revision\t\t\t= 0x%x,\n", revision);
	uint16_t board_rev = SPEX2(SSB_SPROM8_BOARDREV, ~0, 0);
		fprintf(fdout, "\t.board_rev\t\t\t= 0x%x,\n", board_rev);
	uint8_t txpid2g[4];
		txpid2g[0] = SPEX2(SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G0, SSB_SPROM4_TXPID2G0_SHIFT);
		txpid2g[1] = SPEX2(SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G1, SSB_SPROM4_TXPID2G1_SHIFT);
		txpid2g[2] = SPEX2(SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G2, SSB_SPROM4_TXPID2G2_SHIFT);
		txpid2g[3] = SPEX2(SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G3, SSB_SPROM4_TXPID2G3_SHIFT);
		fprintf(fdout, "\t.txpid2g[0]\t\t\t= 0x%x,\n", txpid2g[0]);
		fprintf(fdout, "\t.txpid2g[1]\t\t\t= 0x%x,\n", txpid2g[1]);
		fprintf(fdout, "\t.txpid2g[2]\t\t\t= 0x%x,\n", txpid2g[2]);
		fprintf(fdout, "\t.txpid2g[3]\t\t\t= 0x%x,\n", txpid2g[3]);
	uint8_t txpid5gl[4];
		txpid5gl[0] = SPEX2(SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL0, SSB_SPROM4_TXPID5GL0_SHIFT);
		txpid5gl[1] = SPEX2(SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL1, SSB_SPROM4_TXPID5GL1_SHIFT);
		txpid5gl[2] = SPEX2(SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL2, SSB_SPROM4_TXPID5GL2_SHIFT);
		txpid5gl[3] = SPEX2(SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL3, SSB_SPROM4_TXPID5GL3_SHIFT);
		fprintf(fdout, "\t.txpid5gl[0]\t\t\t= 0x%x,\n", txpid5gl[0]);
		fprintf(fdout, "\t.txpid5gl[1]\t\t\t= 0x%x,\n", txpid5gl[1]);
		fprintf(fdout, "\t.txpid5gl[2]\t\t\t= 0x%x,\n", txpid5gl[2]);
		fprintf(fdout, "\t.txpid5gl[3]\t\t\t= 0x%x,\n", txpid5gl[3]);
	uint8_t txpid5g[4];
		txpid5g[0] = SPEX2(SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G0, SSB_SPROM4_TXPID5G0_SHIFT);
		txpid5g[1] = SPEX2(SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G1, SSB_SPROM4_TXPID5G1_SHIFT);
		txpid5g[2] = SPEX2(SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G2, SSB_SPROM4_TXPID5G2_SHIFT);
		txpid5g[3] = SPEX2(SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G3, SSB_SPROM4_TXPID5G3_SHIFT);
		fprintf(fdout, "\t.txpid5g[0]\t\t\t= 0x%x,\n", txpid5g[0]);
		fprintf(fdout, "\t.txpid5g[1]\t\t\t= 0x%x,\n", txpid5g[1]);
		fprintf(fdout, "\t.txpid5g[2]\t\t\t= 0x%x,\n", txpid5g[2]);
		fprintf(fdout, "\t.txpid5g[3]\t\t\t= 0x%x,\n", txpid5g[3]);
	uint8_t txpid5gh[4];
		txpid5gh[0] = SPEX2(SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH0, SSB_SPROM4_TXPID5GH0_SHIFT);
		txpid5gh[1] = SPEX2(SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH1, SSB_SPROM4_TXPID5GH1_SHIFT);
		txpid5gh[2] = SPEX2(SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH2, SSB_SPROM4_TXPID5GH2_SHIFT);
		txpid5gh[3] = SPEX2(SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH3, SSB_SPROM4_TXPID5GH3_SHIFT);
		fprintf(fdout, "\t.txpid5gh[0]\t\t\t= 0x%x,\n", txpid5gh[0]);
		fprintf(fdout, "\t.txpid5gh[1]\t\t\t= 0x%x,\n", txpid5gh[1]);
		fprintf(fdout, "\t.txpid5gh[2]\t\t\t= 0x%x,\n", txpid5gh[2]);
		fprintf(fdout, "\t.txpid5gh[3]\t\t\t= 0x%x,\n", txpid5gh[3]);
	uint16_t boardflags_lo = SPEX2(SSB_SPROM8_BFLLO, ~0, 0);
		fprintf(fdout, "\t.boardflags_lo\t\t\t= 0x%x,\n", boardflags_lo);
	uint16_t boardflags_hi = SPEX2(SSB_SPROM8_BFLHI, ~0, 0);
		fprintf(fdout, "\t.boardflags_hi\t\t\t= 0x%x,\n", boardflags_hi);
	uint16_t boardflags2_lo = SPEX2(SSB_SPROM8_BFL2LO, ~0, 0);
		fprintf(fdout, "\t.boardflags2_lo\t\t\t= 0x%x,\n", boardflags2_lo);
	uint16_t boardflags2_hi = SPEX2(SSB_SPROM8_BFL2HI, ~0, 0);
		fprintf(fdout, "\t.boardflags2_hi\t\t\t= 0x%x,\n", boardflags2_hi);
	uint8_t country_code = SPEX2(SSB_SPROM8_CCODE, ~0, 0);
		fprintf(fdout, "\t.country_code\t\t\t= 0x%x,\n", country_code);

	uint16_t pwr_info_offset[] = {
		SSB_SROM8_PWR_INFO_CORE0, SSB_SROM8_PWR_INFO_CORE1,
		SSB_SROM8_PWR_INFO_CORE2, SSB_SROM8_PWR_INFO_CORE3
	};
	uint16_t o;
	for (i = 0; i < 4; i++) {
		o = pwr_info_offset[i];

		uint8_t itssi_2g = SPEX2(o + SSB_SROM8_2G_MAXP_ITSSI, SSB_SPROM8_2G_ITSSI, SSB_SPROM8_2G_ITSSI_SHIFT);
			fprintf(fdout, "\t.core_pwr_info[%d].itssi_2g\t= 0x%x,\n", i, itssi_2g);
		uint8_t maxpwr_2g = SPEX2(o + SSB_SROM8_2G_MAXP_ITSSI, SSB_SPROM8_2G_MAXP, 0);
			fprintf(fdout, "\t.core_pwr_info[%d].maxpwr_2g\t= 0x%x,\n", i, maxpwr_2g);
		uint16_t pa_2g[4];
			pa_2g[0] = SPEX2(o + SSB_SROM8_2G_PA_0, ~0, 0);
			pa_2g[1] = SPEX2(o + SSB_SROM8_2G_PA_1, ~0, 0);
			pa_2g[2] = SPEX2(o + SSB_SROM8_2G_PA_2, ~0, 0);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_2g[0]\t= 0x%x,\n", i, pa_2g[0]);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_2g[1]\t= 0x%x,\n", i, pa_2g[1]);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_2g[2]\t= 0x%x,\n", i, pa_2g[2]);
		uint8_t itssi_5g = SPEX2(o + SSB_SROM8_5G_MAXP_ITSSI, SSB_SPROM8_5G_ITSSI, SSB_SPROM8_5G_ITSSI_SHIFT);
			fprintf(fdout, "\t.core_pwr_info[%d].itssi_5g\t= 0x%x,\n", i, itssi_5g);
		uint8_t maxpwr_5g = SPEX2(o + SSB_SROM8_5G_MAXP_ITSSI, SSB_SPROM8_5G_MAXP, 0);
			fprintf(fdout, "\t.core_pwr_info[%d].maxpwr_5g\t= 0x%x,\n", i, maxpwr_5g);
		uint8_t maxpwr_5gh = SPEX2(o + SSB_SPROM8_5GHL_MAXP, SSB_SPROM8_5GH_MAXP, 0);
			fprintf(fdout, "\t.core_pwr_info[%d].maxpwr_5gh\t= 0x%x,\n", i, maxpwr_5gh);
		uint8_t maxpwr_5gl = SPEX2(o + SSB_SPROM8_5GHL_MAXP, SSB_SPROM8_5GL_MAXP, SSB_SPROM8_5GL_MAXP_SHIFT);
			fprintf(fdout, "\t.core_pwr_info[%d].maxpwr_5gl\t= 0x%x,\n", i, maxpwr_5gl);
		uint16_t pa_5gl[4];
			pa_5gl[0] = SPEX2(o + SSB_SROM8_5GL_PA_0, ~0, 0);
			pa_5gl[1] = SPEX2(o + SSB_SROM8_5GL_PA_1, ~0, 0);
			pa_5gl[2] = SPEX2(o + SSB_SROM8_5GL_PA_2, ~0, 0);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5gl[0]\t= 0x%x,\n", i, pa_5gl[0]);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5gl[1]\t= 0x%x,\n", i, pa_5gl[1]);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5gl[2]\t= 0x%x,\n", i, pa_5gl[2]);
		uint16_t pa_5g[4];
			pa_5g[0] = SPEX2(o + SSB_SROM8_5G_PA_0, ~0, 0);
			pa_5g[1] = SPEX2(o + SSB_SROM8_5G_PA_1, ~0, 0);
			pa_5g[2] = SPEX2(o + SSB_SROM8_5G_PA_2, ~0, 0);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5g[0]\t= 0x%x,\n", i, pa_5g[0]);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5g[1]\t= 0x%x,\n", i, pa_5g[1]);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5g[2]\t= 0x%x,\n", i, pa_5g[2]);
		uint16_t pa_5gh[4];
			pa_5gh[0] = SPEX2(o + SSB_SROM8_5GH_PA_0, ~0, 0);
			pa_5gh[1] = SPEX2(o + SSB_SROM8_5GH_PA_1, ~0, 0);
			pa_5gh[2] = SPEX2(o + SSB_SROM8_5GH_PA_2, ~0, 0);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5gh[0]\t= 0x%x,\n", i, pa_5gh[0]);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5gh[1]\t= 0x%x,\n", i, pa_5gh[1]);
			fprintf(fdout, "\t.core_pwr_info[%d].pa_5gh[2]\t= 0x%x,\n", i, pa_5gh[2]);
	}

	uint8_t tssipos_2g = SPEX2(SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TSSIPOS, SSB_SROM8_FEM_TSSIPOS_SHIFT);
		fprintf(fdout, "\t.fem.ghz2.tssipos\t\t= 0x%x,\n", tssipos_2g);
	uint8_t extpa_gain_2g = SPEX2(SSB_SPROM8_FEM2G, SSB_SROM8_FEM_EXTPA_GAIN, SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
		fprintf(fdout, "\t.fem.ghz2.extpa_gain\t\t= 0x%x,\n", extpa_gain_2g);
	uint8_t pdet_range_2g = SPEX2(SSB_SPROM8_FEM2G, SSB_SROM8_FEM_PDET_RANGE, SSB_SROM8_FEM_PDET_RANGE_SHIFT);
		fprintf(fdout, "\t.fem.ghz2.pdet_range\t\t= 0x%x,\n", pdet_range_2g);
	uint8_t tr_iso_2g = SPEX2(SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TR_ISO, SSB_SROM8_FEM_TR_ISO_SHIFT);
		fprintf(fdout, "\t.fem.ghz2.tr_iso\t\t= 0x%x,\n", tr_iso_2g);
	uint8_t antswlut_2g = SPEX2(SSB_SPROM8_FEM2G, SSB_SROM8_FEM_ANTSWLUT, SSB_SROM8_FEM_ANTSWLUT_SHIFT);
		fprintf(fdout, "\t.fem.ghz2.antswlut\t\t= 0x%x,\n", antswlut_2g);
	uint8_t tssipos_5g = SPEX2(SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TSSIPOS, SSB_SROM8_FEM_TSSIPOS_SHIFT);
		fprintf(fdout, "\t.fem.ghz5.tssipos\t\t= 0x%x,\n", tssipos_5g);
	uint8_t extpa_gain_5g = SPEX2(SSB_SPROM8_FEM5G, SSB_SROM8_FEM_EXTPA_GAIN, SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
		fprintf(fdout, "\t.fem.ghz5.extpa_gain\t\t= 0x%x,\n", extpa_gain_5g);
	uint8_t pdet_range_5g = SPEX2(SSB_SPROM8_FEM5G, SSB_SROM8_FEM_PDET_RANGE, SSB_SROM8_FEM_PDET_RANGE_SHIFT);
		fprintf(fdout, "\t.fem.ghz5.pdet_range\t\t= 0x%x,\n", pdet_range_5g);
	uint8_t tr_iso_5g = SPEX2(SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TR_ISO, SSB_SROM8_FEM_TR_ISO_SHIFT);
		fprintf(fdout, "\t.fem.ghz5.tr_iso\t\t= 0x%x,\n", tr_iso_5g);
	uint8_t antswlut_5g = SPEX2(SSB_SPROM8_FEM5G, SSB_SROM8_FEM_ANTSWLUT, SSB_SROM8_FEM_ANTSWLUT_SHIFT);
		fprintf(fdout, "\t.fem.ghz5.antswlut\t\t= 0x%x,\n", antswlut_5g);

	//Footer
	fprintf(fdout, "};\n");

	close(fdin);
	fclose(fdout);

	return 0;
}
