/*! **********************************************************************************************
* 2014  ITESM Campus Guadalajara. Laboratorio de Microcontroladores
*
*
* @file:      types.h
* @author(s):
*
* @brief (User's Manual)
*
**************************************************************************************************/

#ifndef TYPES_H_
#define TYPES_H_


/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define M_TRUE 	(1)
#define M_FALSE (0)

#define M_NULL	(0)

#define M_ENABLE	(1)
#define M_DISABLE	(0)
/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/
typedef unsigned char	u8;
typedef signed char 	i8;
typedef char 		bool;
typedef signed short	i16;
typedef unsigned short	u16;
typedef signed long	i32;
typedef unsigned long	u32;
typedef void (*ISR_callback)(void);
typedef void (*pFunc_t)(void);
/*************************************************************************************************/
/*********************			 	 Functions Like Macros					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Extern Variables					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Extern Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
#endif /* TYPES_H_ */
