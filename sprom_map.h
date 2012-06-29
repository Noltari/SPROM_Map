/**
	SPROM_Map
	@author: Álvaro Fernández Rojas <noltari@gmail.com>
*/

#ifndef MAP_SPROM_EXTRACT_H
#define MAP_SPROM_EXTRACT_H 1

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int sprom_map(int fdin, long fdin_size, FILE* fdout);

#define SPOFF(offset)	((offset) / sizeof(uint16_t))
#define SPEX(_field, _offset, _mask, _shift)	\
	bus->sprom._field = ((sprom[SPOFF(_offset)] & (_mask)) >> (_shift))

#define SPOFF2(offset)	((offset) / sizeof(uint16_t))
#define SPEX2(_offset, _mask, _shift)	\
	((sprom[SPOFF2(_offset)] & (_mask)) >> (_shift))

/* SPROM shadow area. If not otherwise noted, fields are
 * two bytes wide. Note that the SPROM can _only_ be read
 * in two-byte quantities.
 */
#define SSB_SPROMSIZE_WORDS_R4		220
#define  SSB_SPROM_REVISION_REV		0x00FF	/* SPROM Revision number */

/* SPROM Revision 4 */
#define SSB_SPROM4_TXPID2G01		0x0062 	/* TX Power Index 2GHz */
#define  SSB_SPROM4_TXPID2G0		0x00FF
#define  SSB_SPROM4_TXPID2G0_SHIFT	0
#define  SSB_SPROM4_TXPID2G1		0xFF00
#define  SSB_SPROM4_TXPID2G1_SHIFT	8
#define SSB_SPROM4_TXPID2G23		0x0064 	/* TX Power Index 2GHz */
#define  SSB_SPROM4_TXPID2G2		0x00FF
#define  SSB_SPROM4_TXPID2G2_SHIFT	0
#define  SSB_SPROM4_TXPID2G3		0xFF00
#define  SSB_SPROM4_TXPID2G3_SHIFT	8
#define SSB_SPROM4_TXPID5G01		0x0066 	/* TX Power Index 5GHz middle subband */
#define  SSB_SPROM4_TXPID5G0		0x00FF
#define  SSB_SPROM4_TXPID5G0_SHIFT	0
#define  SSB_SPROM4_TXPID5G1		0xFF00
#define  SSB_SPROM4_TXPID5G1_SHIFT	8
#define SSB_SPROM4_TXPID5G23		0x0068 	/* TX Power Index 5GHz middle subband */
#define  SSB_SPROM4_TXPID5G2		0x00FF
#define  SSB_SPROM4_TXPID5G2_SHIFT	0
#define  SSB_SPROM4_TXPID5G3		0xFF00
#define  SSB_SPROM4_TXPID5G3_SHIFT	8
#define SSB_SPROM4_TXPID5GL01		0x006A 	/* TX Power Index 5GHz low subband */
#define  SSB_SPROM4_TXPID5GL0		0x00FF
#define  SSB_SPROM4_TXPID5GL0_SHIFT	0
#define  SSB_SPROM4_TXPID5GL1		0xFF00
#define  SSB_SPROM4_TXPID5GL1_SHIFT	8
#define SSB_SPROM4_TXPID5GL23		0x006C 	/* TX Power Index 5GHz low subband */
#define  SSB_SPROM4_TXPID5GL2		0x00FF
#define  SSB_SPROM4_TXPID5GL2_SHIFT	0
#define  SSB_SPROM4_TXPID5GL3		0xFF00
#define  SSB_SPROM4_TXPID5GL3_SHIFT	8
#define SSB_SPROM4_TXPID5GH01		0x006E 	/* TX Power Index 5GHz high subband */
#define  SSB_SPROM4_TXPID5GH0		0x00FF
#define  SSB_SPROM4_TXPID5GH0_SHIFT	0
#define  SSB_SPROM4_TXPID5GH1		0xFF00
#define  SSB_SPROM4_TXPID5GH1_SHIFT	8
#define SSB_SPROM4_TXPID5GH23		0x0070 	/* TX Power Index 5GHz high subband */
#define  SSB_SPROM4_TXPID5GH2		0x00FF
#define  SSB_SPROM4_TXPID5GH2_SHIFT	0
#define  SSB_SPROM4_TXPID5GH3		0xFF00
#define  SSB_SPROM4_TXPID5GH3_SHIFT	8

/* SPROM Revision 8 */
#define SSB_SPROM8_BOARDREV		0x0082	/* Board revision */
#define SSB_SPROM8_BFLLO		0x0084	/* Board flags (bits 0-15) */
#define SSB_SPROM8_BFLHI		0x0086	/* Board flags (bits 16-31) */
#define SSB_SPROM8_BFL2LO		0x0088	/* Board flags (bits 32-47) */
#define SSB_SPROM8_BFL2HI		0x008A	/* Board flags (bits 48-63) */
#define SSB_SPROM8_IL0MAC		0x008C	/* 6 byte MAC address */
#define SSB_SPROM8_CCODE		0x0092	/* 2 byte country code */
#define SSB_SPROM8_GPIOA		0x0096	/*Gen. Purpose IO # 0 and 1 */
#define  SSB_SPROM8_GPIOA_P0		0x00FF	/* Pin 0 */
#define  SSB_SPROM8_GPIOA_P1		0xFF00	/* Pin 1 */
#define  SSB_SPROM8_GPIOA_P1_SHIFT	8
#define SSB_SPROM8_GPIOB		0x0098	/* Gen. Purpose IO # 2 and 3 */
#define  SSB_SPROM8_GPIOB_P2		0x00FF	/* Pin 2 */
#define  SSB_SPROM8_GPIOB_P3		0xFF00	/* Pin 3 */
#define  SSB_SPROM8_GPIOB_P3_SHIFT	8
#define SSB_SPROM8_ANTAVAIL		0x009C  /* Antenna available bitfields*/
#define  SSB_SPROM8_ANTAVAIL_A		0xFF00	/* A-PHY bitfield */
#define  SSB_SPROM8_ANTAVAIL_A_SHIFT	8
#define  SSB_SPROM8_ANTAVAIL_BG		0x00FF	/* B-PHY and G-PHY bitfield */
#define  SSB_SPROM8_ANTAVAIL_BG_SHIFT	0
#define SSB_SPROM8_AGAIN01		0x009E	/* Antenna Gain (in dBm Q5.2) */
#define  SSB_SPROM8_AGAIN0		0x00FF	/* Antenna 0 */
#define  SSB_SPROM8_AGAIN0_SHIFT	0
#define  SSB_SPROM8_AGAIN1		0xFF00	/* Antenna 1 */
#define  SSB_SPROM8_AGAIN1_SHIFT	8
#define SSB_SPROM8_AGAIN23		0x00A0
#define  SSB_SPROM8_AGAIN2		0x00FF	/* Antenna 2 */
#define  SSB_SPROM8_AGAIN2_SHIFT	0
#define  SSB_SPROM8_AGAIN3		0xFF00	/* Antenna 3 */
#define  SSB_SPROM8_AGAIN3_SHIFT	8
#define SSB_SPROM8_RSSIPARM2G		0x00A4	/* RSSI params for 2GHz */
#define  SSB_SPROM8_RSSISMF2G		0x000F
#define  SSB_SPROM8_RSSISMC2G		0x00F0
#define  SSB_SPROM8_RSSISMC2G_SHIFT	4
#define  SSB_SPROM8_RSSISAV2G		0x0700
#define  SSB_SPROM8_RSSISAV2G_SHIFT	8
#define  SSB_SPROM8_BXA2G		0x1800
#define  SSB_SPROM8_BXA2G_SHIFT		11
#define SSB_SPROM8_RSSIPARM5G		0x00A6	/* RSSI params for 5GHz */
#define  SSB_SPROM8_RSSISMF5G		0x000F
#define  SSB_SPROM8_RSSISMC5G		0x00F0
#define  SSB_SPROM8_RSSISMC5G_SHIFT	4
#define  SSB_SPROM8_RSSISAV5G		0x0700
#define  SSB_SPROM8_RSSISAV5G_SHIFT	8
#define  SSB_SPROM8_BXA5G		0x1800
#define  SSB_SPROM8_BXA5G_SHIFT		11
#define SSB_SPROM8_TRI25G		0x00A8	/* TX isolation 2.4&5.3GHz */
#define  SSB_SPROM8_TRI2G		0x00FF	/* TX isolation 2.4GHz */
#define  SSB_SPROM8_TRI5G		0xFF00	/* TX isolation 5.3GHz */
#define  SSB_SPROM8_TRI5G_SHIFT		8
#define SSB_SPROM8_TRI5GHL		0x00AA	/* TX isolation 5.2/5.8GHz */
#define  SSB_SPROM8_TRI5GL		0x00FF	/* TX isolation 5.2GHz */
#define  SSB_SPROM8_TRI5GH		0xFF00	/* TX isolation 5.8GHz */
#define  SSB_SPROM8_TRI5GH_SHIFT	8
#define SSB_SPROM8_RXPO			0x00AC  /* RX power offsets */
#define  SSB_SPROM8_RXPO2G		0x00FF	/* 2GHz RX power offset */
#define  SSB_SPROM8_RXPO5G		0xFF00	/* 5GHz RX power offset */
#define  SSB_SPROM8_RXPO5G_SHIFT	8
#define SSB_SPROM8_FEM2G		0x00AE
#define SSB_SPROM8_FEM5G		0x00B0
#define  SSB_SROM8_FEM_TSSIPOS		0x0001
#define  SSB_SROM8_FEM_TSSIPOS_SHIFT	0
#define  SSB_SROM8_FEM_EXTPA_GAIN	0x0006
#define  SSB_SROM8_FEM_EXTPA_GAIN_SHIFT	1
#define  SSB_SROM8_FEM_PDET_RANGE	0x00F8
#define  SSB_SROM8_FEM_PDET_RANGE_SHIFT	3
#define  SSB_SROM8_FEM_TR_ISO		0x0700
#define  SSB_SROM8_FEM_TR_ISO_SHIFT	8
#define  SSB_SROM8_FEM_ANTSWLUT		0xF800
#define  SSB_SROM8_FEM_ANTSWLUT_SHIFT	11
#define SSB_SPROM8_THERMAL		0x00B2
#define SSB_SPROM8_MPWR_RAWTS		0x00B4
#define SSB_SPROM8_TS_SLP_OPT_CORRX	0x00B6
#define SSB_SPROM8_FOC_HWIQ_IQSWP	0x00B8
#define SSB_SPROM8_PHYCAL_TEMPDELTA	0x00BA

/* There are 4 blocks with power info sharing the same layout */
#define SSB_SROM8_PWR_INFO_CORE0	0x00C0
#define SSB_SROM8_PWR_INFO_CORE1	0x00E0
#define SSB_SROM8_PWR_INFO_CORE2	0x0100
#define SSB_SROM8_PWR_INFO_CORE3	0x0120

#define SSB_SROM8_2G_MAXP_ITSSI		0x00
#define  SSB_SPROM8_2G_MAXP		0x00FF
#define  SSB_SPROM8_2G_ITSSI		0xFF00
#define  SSB_SPROM8_2G_ITSSI_SHIFT	8
#define SSB_SROM8_2G_PA_0		0x02	/* 2GHz power amp settings */
#define SSB_SROM8_2G_PA_1		0x04
#define SSB_SROM8_2G_PA_2		0x06
#define SSB_SROM8_5G_MAXP_ITSSI		0x08	/* 5GHz ITSSI and 5.3GHz Max Power */
#define  SSB_SPROM8_5G_MAXP		0x00FF
#define  SSB_SPROM8_5G_ITSSI		0xFF00
#define  SSB_SPROM8_5G_ITSSI_SHIFT	8
#define SSB_SPROM8_5GHL_MAXP		0x0A	/* 5.2GHz and 5.8GHz Max Power */
#define  SSB_SPROM8_5GH_MAXP		0x00FF
#define  SSB_SPROM8_5GL_MAXP		0xFF00
#define  SSB_SPROM8_5GL_MAXP_SHIFT	8
#define SSB_SROM8_5G_PA_0		0x0C	/* 5.3GHz power amp settings */
#define SSB_SROM8_5G_PA_1		0x0E
#define SSB_SROM8_5G_PA_2		0x10
#define SSB_SROM8_5GL_PA_0		0x12	/* 5.2GHz power amp settings */
#define SSB_SROM8_5GL_PA_1		0x14
#define SSB_SROM8_5GL_PA_2		0x16
#define SSB_SROM8_5GH_PA_0		0x18	/* 5.8GHz power amp settings */
#define SSB_SROM8_5GH_PA_1		0x1A
#define SSB_SROM8_5GH_PA_2		0x1C

/* TODO: Make it deprecated */
#define SSB_SPROM8_MAXP_BG		0x00C0  /* Max Power 2GHz in path 1 */
#define  SSB_SPROM8_MAXP_BG_MASK	0x00FF  /* Mask for Max Power 2GHz */
#define  SSB_SPROM8_ITSSI_BG		0xFF00	/* Mask for path 1 itssi_bg */
#define  SSB_SPROM8_ITSSI_BG_SHIFT	8
#define SSB_SPROM8_PA0B0		0x00C2	/* 2GHz power amp settings */
#define SSB_SPROM8_PA0B1		0x00C4
#define SSB_SPROM8_PA0B2		0x00C6
#define SSB_SPROM8_MAXP_A		0x00C8  /* Max Power 5.3GHz */
#define  SSB_SPROM8_MAXP_A_MASK		0x00FF  /* Mask for Max Power 5.3GHz */
#define  SSB_SPROM8_ITSSI_A		0xFF00	/* Mask for path 1 itssi_a */
#define  SSB_SPROM8_ITSSI_A_SHIFT	8
#define SSB_SPROM8_MAXP_AHL		0x00CA  /* Max Power 5.2/5.8GHz */
#define  SSB_SPROM8_MAXP_AH_MASK	0x00FF  /* Mask for Max Power 5.8GHz */
#define  SSB_SPROM8_MAXP_AL_MASK	0xFF00  /* Mask for Max Power 5.2GHz */
#define  SSB_SPROM8_MAXP_AL_SHIFT	8
#define SSB_SPROM8_PA1B0		0x00CC	/* 5.3GHz power amp settings */
#define SSB_SPROM8_PA1B1		0x00CE
#define SSB_SPROM8_PA1B2		0x00D0
#define SSB_SPROM8_PA1LOB0		0x00D2	/* 5.2GHz power amp settings */
#define SSB_SPROM8_PA1LOB1		0x00D4
#define SSB_SPROM8_PA1LOB2		0x00D6
#define SSB_SPROM8_PA1HIB0		0x00D8	/* 5.8GHz power amp settings */
#define SSB_SPROM8_PA1HIB1		0x00DA
#define SSB_SPROM8_PA1HIB2		0x00DC

#define SSB_SPROM8_CCK2GPO		0x0140	/* CCK power offset */
#define SSB_SPROM8_OFDM2GPO		0x0142	/* 2.4GHz OFDM power offset */
#define SSB_SPROM8_OFDM5GPO		0x0146	/* 5.3GHz OFDM power offset */
#define SSB_SPROM8_OFDM5GLPO		0x014A	/* 5.2GHz OFDM power offset */
#define SSB_SPROM8_OFDM5GHPO		0x014E	/* 5.8GHz OFDM power offset */

#endif
