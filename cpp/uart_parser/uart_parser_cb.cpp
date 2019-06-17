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
    frame.push_back(2);
    return frame;
}

std::vector<uint8_t> gen_vmem_imem_ptr_frame() {
    std::vector<uint8_t> frame;
    frame.push_back(3);
    frame.push_back(11);
    frame.push_back(7);
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
    frame.push_back(2);
    return frame;
}

std::vector<uint8_t> gen_trigger_frame() {
    std::vector<uint8_t> frame;
    frame.push_back(5);
    frame.push_back(2);
    return frame;
}

typedef std::function<void(std::vector<uint8_t>*)> uart_cb_t;
std::vector<uart_cb_t> uart_callbacks;

typedef std::function<void(uint8_t, uint32_t, std::vector<uint32_t>*)> vmem_imem_uart_cb_t;
std::vector<vmem_imem_uart_cb_t> vmem_imem_uart_callbacks;

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
    get_byte(frame);
    std::cout << "Literal frame received" << std::endl;
}

std::vector<uint32_t> get_vmem_imem_data(uint32_t addr, uint32_t len) {
    std::vector<uint32_t> data;
    for(int i = 0; i < 10; i++) {
	data.push_back(i);
    }
    return data;
}

void test_cb(uint8_t tag, uint32_t addr, std::vector<uint32_t> *data) {
    std::cout << "TAG: " << int(tag) << " ADDR: " << std::hex << int(addr) << std::endl;
    for(auto& it : *data) {
	std::cout << int(it) << std::endl;
    }
}

void vmem_imem_ptr_frame(std::vector<uint8_t> *frame) {
    uint8_t len = get_byte(frame);
    uint8_t tag;
    uint32_t addr,ptr_len;
    if(len != 11) {
	std::cout << "UART frame length error - expected: 13 actual: " << int(len) << std::endl;
    }
    tag = get_byte(frame);
    //std::cout << "TAG: " << int(tag) << std::endl;
    addr = get_word(frame);
    //std::cout << "ADDR: " << std::hex << addr << std::endl;
    ptr_len = get_word(frame);
    //std::cout << std::hex << addr << " " << ptr_len << std::endl;
    std::vector<uint32_t> data = get_vmem_imem_data(addr, ptr_len);
    for(auto& cb : vmem_imem_uart_callbacks) {
	cb(tag, addr, &data);
    }
}

void data_path_frame(std::vector<uint8_t> *frame) {
    get_byte(frame);
    std::cout << "Datapath frame received" << std:: endl;
}

void trigger_frame(std::vector<uint8_t> *frame) {
    get_byte(frame);
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
	//break;
    case 1: //char
	//uart_callbacks[type](frame);
	//break;
    case 2: //literal
	//break;
    case 3: // vmem_imem_ptr_frame
	//vmem_imem_ptr_frame();
	//break;
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

void parser(uint8_t byte) {
    static std::vector<uint8_t> frame;
    static int length_counter = 0;
    static int length = 0;
    if(frame.size() > 0) {
	frame.push_back(byte);
	length_counter++;
	length = (length == 0) ? byte:length;
	if(length != 0 && length == length_counter) {
	    //std::cout << int(byte) << " " << length << " : " << length_counter << std::endl;
	    parse_frame(&frame);
	    length = 0;
	    length_counter = 0;
	} 
    } else {
	if(byte == 0) {
	    std::cout << "JAM Frame recieved" << std::endl;
	} else if(byte < 6) {
	    frame.push_back(byte);
	    length_counter++;
	} else {
	    std::cout << "Invalid frame" << std::endl;
	}
	
	//std::cout << int(byte) << std::endl;
	
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

    vmem_imem_uart_callbacks.push_back(&test_cb);

    vmem_imem_uart_callbacks.push_back([](uint8_t tag, uint32_t addr, std::vector<uint32_t> *data)
				       {
					   std::cout << "Lambda function" << std::endl;
					   std::cout << "TAG: " << int(tag) << " ADDR: " << std::hex << int(addr) << std::endl;
					   for(auto& it : *data) {
					       std::cout << int(it) << std::endl;
					   }
				       });
    
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

    
    for(auto& it : words) {
	parser(it);
    }

    parser(0);
    
    return 0;
}
