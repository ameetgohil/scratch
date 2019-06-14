#include <vector>
#include <cstdint>
#include <iostream>
#include <functional>


uint8_t get_byte(std::vector<uint8_t> *frame) {
    uint8_t word = frame->front();
    frame->erase(frame->begin());
    return word;
}

uint32_t get_word(std::vector<uint8_t> *frame) {
    uint32_t word = get_byte(frame);
    word |= get_byte(frame) << 8;
    word |= get_byte(frame) << 16;
    word |= get_byte(frame) << 24;
    return word;
}
    
std::vector<uint8_t> gen_jam_frame() {
    std::vector<uint8_t> frame;
    frame.push_back(0);
    return frame;
}

std::vector<uint8_t> gen_char_frame() {
    std::vector<uint8_t> frame;
    frame.push_back(1);
    frame.push_back(13);
    frame.push_back('H');
    frame.push_back('e');
    frame.push_back('l');
    frame.push_back('l');
    frame.push_back('o');

    frame.push_back('\n');
    
    frame.push_back('W');
    frame.push_back('o');
    frame.push_back('r');
    frame.push_back('l');
    frame.push_back('d');
    
    return frame;
}

std::vector<uint8_t> gen_literal_frame() {
    std::vector<uint8_t> frame;
    frame.push_back(2);
    return frame;
}

std::vector<uint8_t> gen_vmem_imem_ptr_frame() {
    std::vector<uint8_t> frame;
    frame.push_back(3);
    frame.push_back(10);
    frame.push_back(0x4);
    frame.push_back(0x3);
    frame.push_back(0x2);
    frame.push_back(0x1);
    frame.push_back(0xA);
    frame.push_back(0xB);
    frame.push_back(0xC);
    frame.push_back(0xD);
    return frame;
}

std::vector<uint8_t> gen_data_path_frame() {
    std::vector<uint8_t> frame;
    frame.push_back(4);
    return frame;
}

std::vector<uint8_t> gen_trigger_frame() {
    std::vector<uint8_t> frame;
    frame.push_back(5);
    return frame;
}

typedef std::function<void(std::vector<uint8_t>*)> uart_cb_t;
std::vector<uart_cb_t> uart_callbacks;

void jam_frame(std::vector<uint8_t> *frame) {
    std::cout << "JAM FRAME" << std::endl;
}

void char_frame(std::vector<uint8_t> *frame) {
    uint8_t len;
    std::string s;
    len = get_byte(frame);
    s.append(frame->begin(), frame->begin() + len -2);
    frame->erase(frame->begin(), frame->begin() + len -2);
    std::cout << "UART msg: " << s << std::endl;
}

void literal_frame(std::vector<uint8_t> *frame) {
    std::cout << "Literal frame received" << std::endl;
}

void vmem_imem_ptr_frame(std::vector<uint8_t> *frame) {
    uint8_t len = get_byte(frame);
    uint32_t addr,ptr_len;
    if(len != 10) {
	std::cout << "UART frame length error - expected: 13 actual: " << int(len) << std::endl;
    }
    addr = get_word(frame);
    ptr_len = get_word(frame);
    std::cout << std::hex << addr << " " << ptr_len << std::endl;
}

void data_path_frame(std::vector<uint8_t> *frame) {
    std::cout << "Datapath frame received" << std:: endl;
}

void trigger_frame(std::vector<uint8_t> *frame) {
    std::cout << "Trigger frame received" << std::endl;
}

int parse_frame(std::vector<uint8_t> *frame) {
    uint8_t len;
    std::string s;
    uint32_t addr = 0;
    uint32_t ptr_len = 0;
    uint8_t type = get_byte(frame);
    switch(type) {
    case 0: //jam
    case 1: //char
    case 2: //literal
    case 3: // vmem_imem_ptr_frame
    case 4: // data path frame
    case 5: //trigger frame
	uart_callbacks[type](frame);
	break;
    default:
	std::cout << "Frame type invalid" << std::endl;
	return -1;
    }

    return 0;
}

void parser(std::vector<uint8_t> words) {
    int ret_code = 0;
    while(ret_code == 0 && words.size() > 0) {
	parse_frame(&words);
    }
}
    

int main() {
    std::vector<uint8_t> frame;
    std::vector<int> range(10);
    int i = 0;
    for(auto& it : range) {
	frame.push_back(i+0x50);
	i++; 
    }
    for(auto& it : frame) {
	std::cout << it << std::endl;
    }

    uart_callbacks.push_back(&jam_frame); //0
    uart_callbacks.push_back(&char_frame); //1
    uart_callbacks.push_back(&literal_frame); //2
    uart_callbacks.push_back(&vmem_imem_ptr_frame); //3
    uart_callbacks.push_back(&data_path_frame); //4
    uart_callbacks.push_back(&trigger_frame); //5
    

    std::vector<uint8_t> words;
    std::vector<uint8_t> gen;
    gen = gen_jam_frame();
    words.insert(words.end(), gen.begin(), gen.end());
    gen = gen_char_frame();
    words.insert(words.end(), gen.begin(), gen.end());
    gen = gen_literal_frame();
    words.insert(words.end(), gen.begin(), gen.end());
    gen = gen_vmem_imem_ptr_frame();
    words.insert(words.end(), gen.begin(), gen.end());
    gen = gen_data_path_frame();
    words.insert(words.end(), gen.begin(), gen.end());
    gen = gen_trigger_frame();
    words.insert(words.end(), gen.begin(), gen.end());
    gen = gen_trigger_frame();
    words.insert(words.end(), gen.begin(), gen.end());
    gen = gen_trigger_frame();
    words.insert(words.end(), gen.begin(), gen.end());
    gen = gen_trigger_frame();
    words.insert(words.end(), gen.begin(), gen.end());
    gen = gen_jam_frame();
    words.insert(words.end(), gen.begin(), gen.end());

    


    words.insert(words.end(), frame.begin(), frame.end());
    
    parser(words);
    
    return 0;
}
