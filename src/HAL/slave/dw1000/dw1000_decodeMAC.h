#ifndef DW1000_FRAME_DECODE_H_
#define DW1000_FRAME_DECODE_H_

extern uint8_t frame_src_addr_index_start_table[];
extern uint8_t frame_len_table[];
extern uint8_t pan_id_index_table[];
extern uint8_t dest_addr_index_table[];
extern uint8_t src_addr_index_table[];
extern uint8_t msg_index_table[];
extern uint8_t fn_code_index_table[];
extern uint32_t(*poll_resp_final_handler_table[])(); 
extern uint32_t(*const dw_handler_table[])();

uint32_t dw_decodeFrameIn(void* host_object, int(*host_usart)(), void* ext_dev_object);


#endif
