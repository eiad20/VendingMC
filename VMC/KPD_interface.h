/***********************************************************/
/*****************    Name : Mahmoud Moner *****************/
/*****************    Date : 25/8/2023     *****************/
/*****************    SWC  : KPD           *****************/
/***************** Virsion :  1.0          *****************/
/***********************************************************/

#ifndef KPD_INTERFACE_H
#define KPD_INTERFACE_H

#define KPD_u8_KEY_NOT_PRESSED        0xff

#define KPD_u8_DIVIDED_BY_ZERO       0xfff

u8 KPD_u8GetKeyState(u8 * Copy_pu8ReturnedKey);

int eval_expression(u8 *str);

int Pass_intPassword (u8 *str);


#endif
