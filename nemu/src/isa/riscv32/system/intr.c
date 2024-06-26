/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/
#include <isa.h>
#include "../local-include/reg.h"
void isa_reg_display();
word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
	sr(MEPC) = epc;
	sr(MCAUSE) = NO;
#ifdef CONFIG_ETRACE
	Log("Exception Trace: PC=0x%08x status: %d cause: %d\n", epc, sr(MSTATUS),sr(MCAUSE));
#endif
	//printf("Start raise. mepc:0x%08x, mcause: %d, mtvec:0x%08x\n",sr(MEPC),sr(MCAUSE),sr(MTVEC));
	//isa_reg_display();
	return sr(MTVEC);
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
