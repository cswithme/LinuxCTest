/*
 * SocketRW.h
 *
 *  Created on: 2019-10-24
 *      Author: root
 */

#ifndef SOCKETRW_H_
#define SOCKETRW_H_

#include <stdint.h>

//ret send byte -1:faile
int SocketWrite(int socketfd, const uint8_t *u8TxDate, uint32_t u32TxLen);

/*
 * u8RxDate: Rx Buff
 * u32RxBuffLen: sizeof(u8RxDate)
 *
 * ret: read len, -1 error
 */
int SocketRead(int socketfd, uint8_t *u8RxDate, uint32_t u32RxBuffLen);

void SocketRWTest(int socketfd);
#endif /* SOCKETRW_H_ */
