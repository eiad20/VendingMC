# ifndef BIT_MATH_H
# define BIT_MATH_H


# define SET_BIT(X,BIT_NUM) 	  X |= (1<<BIT_NUM)
	 
# define CLR_BIT(X,BIT_NUM)          X &= (~(1<<BIT_NUM))
	 
# define TOG_BIT(X,BIT_NUM)       X ^= (1<<BIT_NUM)
	 
# define GET_BIT(X,BIT_NUM)     ((X>>BIT_NUM) & 1)

	 

#endif
