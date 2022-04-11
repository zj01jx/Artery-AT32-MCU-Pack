#include "sys.h"

//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
void WFI_SET(void)
{
  __ASM volatile("wfi");		  
}

//�ر������ж�
void INTX_DISABLE(void)
{		  
  __ASM volatile("cpsid i");
}

//���������ж�
void INTX_ENABLE(void)
{
  __ASM volatile("cpsie i");		  
}

//����ջ����ַ
//addr:ջ����ַ
#if defined (__CC_ARM)
__asm void MSR_MSP(u32 addr) 
{
   MSR MSP, r0 			//set Main Stack value
   BX r14
}
#elif defined (__ICCARM__)
__INLINE void MSR_MSP(u32 addr) 
{
   __ASM("MSR MSP, r0"); 			//set Main Stack value
   __ASM("BX r14");
}
#endif


