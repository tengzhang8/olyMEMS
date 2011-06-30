#define FLASH_CSN	PD4
#define	FLASH_SCK	PD5
#define FLASH_MOSI	PD3
#define FLASH_MISO  PD2


//Flash OPCODES
#define WR_ENABLE	0x06
#define RD_STATUS	0x05
#define RD_ARRAY	0x03
#define	BK_ERASE4	0x20
#define BK_ERASE32	0x52
#define BK_ERASE64	0xD8
#define BP_PROGRAM	0x02
#define WR_STATUS 	0x01

void flash_init();
void flash_csn_low();
void flash_csn_high();
uint8_t flash_transfer_byte(uint8_t byte);
void write_enable();
void flash_program(uint8_t address[3], uint8_t *data, int len);
void flash_read(uint8_t address[3], uint8_t *data, int len);
void block_erase(uint8_t address[3], uint8_t byte);
uint8_t flash_busy();
void write_status_reg(uint8_t byte);


//STORING AND READING DOUBLES
//flash_program(flash_address,(const void*)&d_test,sizeof(double));
//flash_read(flash_address,(void*)&test_buffer,sizeof(double));
