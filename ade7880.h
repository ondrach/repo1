

#ifndef ADE7880_H_
#define ADE7880_H_


#define BLOCK_SIZE 1

/* Writes data to ADE7880 */
extern void ADE_Write( uint8_t TxData[], uint8_t Nr_Bytes);




/* ADE7880 SPI interface select */
void ADE_SPISel(void);

void ADE_SPIInit(void);


#endif /* ADE7880_H_ */
