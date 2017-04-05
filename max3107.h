#ifndef _MAX3107_H
#define _MAX3107_H

/* Custom prototypes and structs */
struct _3107_group;

struct _3107_data {
	char* name;
	struct _3107_group* group;
	int present;
	unsigned short address;
	int index;
	struct i2c_client i2cClient;
	int active;

	unsigned dtrGPIO, dsrGPIO, carGPIO, rngGPIO;

	struct uart_port uartPort;
	int uartclk;
	unsigned interrupts;

	struct work_struct worker;

	struct semaphore sem;
};

struct _3107_group {
	int i2cBus;
	int irqLine, irqBitMask, irqHandlerInstalled;

	unsigned interrupts;
	struct uart_driver uartDriver;

	int uartDriverRegistered;

	unsigned portCount;

	struct _3107_data ports[4];
	struct _3107_data* interruptHistory[4];
	struct work_struct interruptWorker;
};

extern struct _3107_group groups[];
extern struct workqueue_struct* wq;
extern struct i2c_driver 3107_i2c_driver;
extern struct uart_ops max3107_uart_ops;


/* MAX3107 register definitions */
#define MAX3107_RHR_REG			(0x00) /* RX FIFO */
#define MAX3107_THR_REG			(0x00) /* TX FIFO */
#define MAX3107_IRQEN_REG		(0x01) /* IRQ enable */
#define MAX3107_IRQSTS_REG		(0x02) /* IRQ status */
#define MAX3107_LSR_IRQEN_REG		(0x03) /* LSR IRQ enable */
#define MAX3107_LSR_IRQSTS_REG		(0x04) /* LSR IRQ status */
#define MAX3107_SPCHR_IRQEN_REG		(0x05) /* Special char IRQ enable */
#define MAX3107_SPCHR_IRQSTS_REG 	(0x06) /* Special char IRQ status */
#define MAX3107_STS_IRQEN_REG		(0x07) /* Status IRQ enable */
#define MAX3107_STS_IRQSTS_REG		(0x08) /* Status IRQ status */
#define MAX3107_MODE1_REG		(0x09) /* MODE1 */
#define MAX3107_MODE2_REG		(0x0a) /* MODE2 */
#define MAX3107_LCR_REG			(0x0b) /* LCR */
#define MAX3107_RXTO_REG		(0x0c) /* RX timeout */
#define MAX3107_HDPIXDELAY_REG		(0x0d) /* Auto transceiver delays */
#define MAX3107_IRDA_REG		(0x0e) /* IRDA settings */
#define MAX3107_FLOWLVL_REG		(0x0f) /* Flow control levels */
#define MAX3107_FIFOTRIGLVL_REG		(0x10) /* FIFO IRQ trigger levels */
#define MAX3107_TXFIFOLVL_REG		(0x11) /* TX FIFO level */
#define MAX3107_RXFIFOLVL_REG		(0x12) /* RX FIFO level */
#define MAX3107_FLOWCTRL_REG		(0x13) /* Flow control */
#define MAX3107_XON1_REG		(0x14) /* XON1 character */
#define MAX3107_XON2_REG		(0x15) /* XON2 character */
#define MAX3107_XOFF1_REG		(0x16) /* XOFF1 character */
#define MAX3107_XOFF2_REG		(0x17) /* XOFF2 character */
#define MAX3107_GPIOCFG_REG		(0x18) /* GPIO config */
#define MAX3107_GPIODATA_REG		(0x19) /* GPIO data */
#define MAX3107_PLLCFG_REG		(0x1a) /* PLL config */
#define MAX3107_BRGCFG_REG		(0x1b) /* Baud rate generator conf */
#define MAX3107_BRGDIVLSB_REG		(0x1c) /* Baud rate divisor LSB */
#define MAX3107_BRGDIVMSB_REG		(0x1d) /* Baud rate divisor MSB */
#define MAX3107_CLKSRC_REG		(0x1e) /* Clock source */
/* Only present in MAX3107 */
#define MAX3107_REVID_REG		(0x1f) /* Revision identification */

/* IRQ register bits */
#define MAX3107_IRQ_LSR_BIT		(1 << 0) /* LSR interrupt */
#define MAX3107_IRQ_SPCHR_BIT		(1 << 1) /* Special char interrupt */
#define MAX3107_IRQ_STS_BIT		(1 << 2) /* Status interrupt */
#define MAX3107_IRQ_RXFIFO_BIT		(1 << 3) /* RX FIFO interrupt */
#define MAX3107_IRQ_TXFIFO_BIT		(1 << 4) /* TX FIFO interrupt */
#define MAX3107_IRQ_TXEMPTY_BIT		(1 << 5) /* TX FIFO empty interrupt */
#define MAX3107_IRQ_RXEMPTY_BIT		(1 << 6) /* RX FIFO empty interrupt */
#define MAX3107_IRQ_CTS_BIT		(1 << 7) /* CTS interrupt */

/* LSR register bits */
#define MAX3107_LSR_RXTO_BIT		(1 << 0) /* RX timeout */
#define MAX3107_LSR_RXOVR_BIT		(1 << 1) /* RX overrun */
#define MAX3107_LSR_RXPAR_BIT		(1 << 2) /* RX parity error */
#define MAX3107_LSR_FRERR_BIT		(1 << 3) /* Frame error */
#define MAX3107_LSR_RXBRK_BIT		(1 << 4) /* RX break */
#define MAX3107_LSR_RXNOISE_BIT		(1 << 5) /* RX noise */
#define MAX3107_LSR_CTS_BIT		(1 << 7) /* CTS pin state */

/* Special character register bits */
#define MAX3107_SPCHR_XON1_BIT		(1 << 0) /* XON1 character */
#define MAX3107_SPCHR_XON2_BIT		(1 << 1) /* XON2 character */
#define MAX3107_SPCHR_XOFF1_BIT		(1 << 2) /* XOFF1 character */
#define MAX3107_SPCHR_XOFF2_BIT		(1 << 3) /* XOFF2 character */
#define MAX3107_SPCHR_BREAK_BIT		(1 << 4) /* RX break */
#define MAX3107_SPCHR_MULTIDROP_BIT	(1 << 5) /* 9-bit multidrop addr char */

/* Status register bits */
#define MAX3107_STS_GPIO0_BIT		(1 << 0) /* GPIO 0 interrupt */
#define MAX3107_STS_GPIO1_BIT		(1 << 1) /* GPIO 1 interrupt */
#define MAX3107_STS_GPIO2_BIT		(1 << 2) /* GPIO 2 interrupt */
#define MAX3107_STS_GPIO3_BIT		(1 << 3) /* GPIO 3 interrupt */
#define MAX3107_STS_CLKREADY_BIT	(1 << 5) /* Clock ready */
#define MAX3107_STS_SLEEP_BIT		(1 << 6) /* Sleep interrupt */

/* MODE1 register bits */
#define MAX3107_MODE1_RXDIS_BIT		(1 << 0) /* RX disable */
#define MAX3107_MODE1_TXDIS_BIT		(1 << 1) /* TX disable */
#define MAX3107_MODE1_TXHIZ_BIT		(1 << 2) /* TX pin three-state */
#define MAX3107_MODE1_RTSHIZ_BIT	(1 << 3) /* RTS pin three-state */
#define MAX3107_MODE1_TRNSCVCTRL_BIT	(1 << 4) /* Transceiver ctrl enable */
#define MAX3107_MODE1_FORCESLEEP_BIT	(1 << 5) /* Force sleep mode */
#define MAX3107_MODE1_AUTOSLEEP_BIT	(1 << 6) /* Auto sleep enable */
#define MAX3107_MODE1_IRQSEL_BIT	(1 << 7) /* IRQ pin enable */

/* MODE2 register bits */
#define MAX3107_MODE2_RST_BIT		(1 << 0) /* Chip reset */
#define MAX3107_MODE2_FIFORST_BIT	(1 << 1) /* FIFO reset */
#define MAX3107_MODE2_RXTRIGINV_BIT	(1 << 2) /* RX FIFO INT invert */
#define MAX3107_MODE2_RXEMPTINV_BIT	(1 << 3) /* RX FIFO empty INT invert */
#define MAX3107_MODE2_SPCHR_BIT		(1 << 4) /* Special chr detect enable */
#define MAX3107_MODE2_LOOPBACK_BIT	(1 << 5) /* Internal loopback enable */
#define MAX3107_MODE2_MULTIDROP_BIT	(1 << 6) /* 9-bit multidrop enable */
#define MAX3107_MODE2_ECHOSUPR_BIT	(1 << 7) /* ECHO suppression enable */

/* LCR register bits */
#define MAX3107_LCR_LENGTH0_BIT		(1 << 0) /* Word length bit 0 */
#define MAX3107_LCR_LENGTH1_BIT		(1 << 1) /* Word length bit 1
						  *
						  * Word length bits table:
						  * 00 -> 5 bit words
						  * 01 -> 6 bit words
						  * 10 -> 7 bit words
						  * 11 -> 8 bit words
						  */
#define MAX3107_LCR_STOPLEN_BIT		(1 << 2) /* STOP length bit
						  *
						  * STOP length bit table:
						  * 0 -> 1 stop bit
						  * 1 -> 1-1.5 stop bits if
						  *      word length is 5,
						  *      2 stop bits otherwise
						  */
#define MAX3107_LCR_PARITY_BIT		(1 << 3) /* Parity bit enable */
#define MAX3107_LCR_EVENPARITY_BIT	(1 << 4) /* Even parity bit enable */
#define MAX3107_LCR_FORCEPARITY_BIT	(1 << 5) /* 9-bit multidrop parity */
#define MAX3107_LCR_TXBREAK_BIT		(1 << 6) /* TX break enable */
#define MAX3107_LCR_RTS_BIT		(1 << 7) /* RTS pin control */
#define MAX3107_LCR_WORD_LEN_5		(0x00)
#define MAX3107_LCR_WORD_LEN_6		(0x01)
#define MAX3107_LCR_WORD_LEN_7		(0x02)
#define MAX3107_LCR_WORD_LEN_8		(0x03)

/* IRDA register bits */
#define MAX3107_IRDA_IRDAEN_BIT		(1 << 0) /* IRDA mode enable */
#define MAX3107_IRDA_SIR_BIT		(1 << 1) /* SIR mode enable */
#define MAX3107_IRDA_SHORTIR_BIT	(1 << 2) /* Short SIR mode enable */
#define MAX3107_IRDA_MIR_BIT		(1 << 3) /* MIR mode enable */
#define MAX3107_IRDA_RXINV_BIT		(1 << 4) /* RX logic inversion enable */
#define MAX3107_IRDA_TXINV_BIT		(1 << 5) /* TX logic inversion enable */

/* Flow control trigger level register masks */
#define MAX3107_FLOWLVL_HALT_MASK	(0x000f) /* Flow control halt level */
#define MAX3107_FLOWLVL_RES_MASK	(0x00f0) /* Flow control resume level */
#define MAX3107_FLOWLVL_HALT(words)	((words / 8) & 0x0f)
#define MAX3107_FLOWLVL_RES(words)	(((words / 8) & 0x0f) << 4)

/* FIFO interrupt trigger level register masks */
#define MAX3107_FIFOTRIGLVL_TX_MASK	(0x0f) /* TX FIFO trigger level */
#define MAX3107_FIFOTRIGLVL_RX_MASK	(0xf0) /* RX FIFO trigger level */
#define MAX3107_FIFOTRIGLVL_TX(words)	((words / 8) & 0x0f)
#define MAX3107_FIFOTRIGLVL_RX(words)	(((words / 8) & 0x0f) << 4)

/* Flow control register bits */
#define MAX3107_FLOWCTRL_AUTORTS_BIT	(1 << 0) /* Auto RTS flow ctrl enable */
#define MAX3107_FLOWCTRL_AUTOCTS_BIT	(1 << 1) /* Auto CTS flow ctrl enable */
#define MAX3107_FLOWCTRL_GPIADDR_BIT	(1 << 2) /* Enables that GPIO inputs
						  * are used in conjunction with
						  * XOFF2 for definition of
						  * special character */
#define MAX3107_FLOWCTRL_SWFLOWEN_BIT	(1 << 3) /* Auto SW flow ctrl enable */
#define MAX3107_FLOWCTRL_SWFLOW0_BIT	(1 << 4) /* SWFLOW bit 0 */
#define MAX3107_FLOWCTRL_SWFLOW1_BIT	(1 << 5) /* SWFLOW bit 1
						  *
						  * SWFLOW bits 1 & 0 table:
						  * 00 -> no transmitter flow
						  *       control
						  * 01 -> receiver compares
						  *       XON2 and XOFF2
						  *       and controls
						  *       transmitter
						  * 10 -> receiver compares
						  *       XON1 and XOFF1
						  *       and controls
						  *       transmitter
						  * 11 -> receiver compares
						  *       XON1, XON2, XOFF1 and
						  *       XOFF2 and controls
						  *       transmitter
						  */
#define MAX3107_FLOWCTRL_SWFLOW2_BIT	(1 << 6) /* SWFLOW bit 2 */
#define MAX3107_FLOWCTRL_SWFLOW3_BIT	(1 << 7) /* SWFLOW bit 3
						  *
						  * SWFLOW bits 3 & 2 table:
						  * 00 -> no received flow
						  *       control
						  * 01 -> transmitter generates
						  *       XON2 and XOFF2
						  * 10 -> transmitter generates
						  *       XON1 and XOFF1
						  * 11 -> transmitter generates
						  *       XON1, XON2, XOFF1 and
						  *       XOFF2
						  */

/* GPIO configuration register bits */
#define MAX3107_GPIOCFG_GP0OUT_BIT	(1 << 0) /* GPIO 0 output enable */
#define MAX3107_GPIOCFG_GP1OUT_BIT	(1 << 1) /* GPIO 1 output enable */
#define MAX3107_GPIOCFG_GP2OUT_BIT	(1 << 2) /* GPIO 2 output enable */
#define MAX3107_GPIOCFG_GP3OUT_BIT	(1 << 3) /* GPIO 3 output enable */
#define MAX3107_GPIOCFG_GP0OD_BIT	(1 << 4) /* GPIO 0 open-drain enable */
#define MAX3107_GPIOCFG_GP1OD_BIT	(1 << 5) /* GPIO 1 open-drain enable */
#define MAX3107_GPIOCFG_GP2OD_BIT	(1 << 6) /* GPIO 2 open-drain enable */
#define MAX3107_GPIOCFG_GP3OD_BIT	(1 << 7) /* GPIO 3 open-drain enable */

/* GPIO DATA register bits */
#define MAX3107_GPIODATA_GP0OUT_BIT	(1 << 0) /* GPIO 0 output value */
#define MAX3107_GPIODATA_GP1OUT_BIT	(1 << 1) /* GPIO 1 output value */
#define MAX3107_GPIODATA_GP2OUT_BIT	(1 << 2) /* GPIO 2 output value */
#define MAX3107_GPIODATA_GP3OUT_BIT	(1 << 3) /* GPIO 3 output value */
#define MAX3107_GPIODATA_GP0IN_BIT	(1 << 4) /* GPIO 0 input value */
#define MAX3107_GPIODATA_GP1IN_BIT	(1 << 5) /* GPIO 1 input value */
#define MAX3107_GPIODATA_GP2IN_BIT	(1 << 6) /* GPIO 2 input value */
#define MAX3107_GPIODATA_GP3IN_BIT	(1 << 7) /* GPIO 3 input value */

/* PLL configuration register masks */
#define MAX3107_PLLCFG_PREDIV_MASK	(0x3f) /* PLL predivision value */
#define MAX3107_PLLCFG_PLLFACTOR_MASK	(0xc0) /* PLL multiplication factor */

/* Baud rate generator configuration register bits */
#define MAX3107_BRGCFG_2XMODE_BIT	(1 << 4) /* Double baud rate */
#define MAX3107_BRGCFG_4XMODE_BIT	(1 << 5) /* Quadruple baud rate */

/* Clock source register bits */
#define MAX3107_CLKSRC_CRYST_BIT	(1 << 1) /* Crystal osc enable */
#define MAX3107_CLKSRC_PLL_BIT		(1 << 2) /* PLL enable */
#define MAX3107_CLKSRC_PLLBYP_BIT	(1 << 3) /* PLL bypass */
#define MAX3107_CLKSRC_EXTCLK_BIT	(1 << 4) /* External clock enable */
#define MAX3107_CLKSRC_CLK2RTS_BIT	(1 << 7) /* Baud clk to RTS pin */

/* Misc definitions */
#define MAX3107_FIFO_SIZE		(128)

/* MAX3107 specific */
#define MAX3107_REV_ID			(0xa0)
#define MAX3107_REV_MASK		(0xfe)

/* IRQ status bits definitions */
#define MAX3107_IRQ_TX			(MAX3107_IRQ_TXFIFO_BIT | \
					 MAX3107_IRQ_TXEMPTY_BIT)
#define MAX3107_IRQ_RX			(MAX3107_IRQ_RXFIFO_BIT | \
					 MAX3107_IRQ_RXEMPTY_BIT)

#endif /* _MAX3107_H */
