#include "button.h"

void check_button(void){
	int e=-1;
	if ((BUTTON & (1<<PC0))) {
		e=0;
	}
	if ((BUTTON & (1<<PC1))) {
		e=1;
	}
	if ((BUTTON & (1<<PC2))) {
		e=2;
	}
	if ((BUTTON & (1<<PC3))) {
		e=3;
	}
	//if (e==-1) return 0;
	if (e==0){
		dir_x = -1;
		dir_y = 0;
		}else if (e==1){
		dir_x = 0;
		dir_y = -1;
		}else if (e==2){
		dir_x = 0;
		dir_y = 1;
		}else if (e==3){
		dir_x = 1;
		dir_y = 0;
	}
}





// Update code tích hợp Chống rung - Debounce ^^
void check_button(void){
    static uint8_t last_button = 0xFF; // Định nghĩa các nút ban đầu chưa được nhấn
    uint8_t current_button = PIND & 0x0F; // Đọc toàn bộ PORTD và lấy 4 bit cuối (tức là bit PD0 -> PD3)
    
    // Xử lý chống rung khi trạng thái button thay đổi
    if (current_button == last_button) return;
    last_button = current_button; 
    
	// Tạo biến vị trí con rắn tạm, nếu k có nút nào nhấn thì vị trí giữ nguyên.
    int8_t new_dir_x = dir_x;
    int8_t new_dir_y = dir_y;
    
    if ((PIND & (1 << PD0)) == 0) { //PD0 nhấn, rắn di chuyển lên TRÊN
        new_dir_x = -1;
        new_dir_y = 0;
    }
    else if ((PIND & (1 << PD1)) == 0) { //PD1 nhấn, rắn di chuyển sang TRÁI
        new_dir_x = 0;
        new_dir_y = -1;
    }
    else if ((PIND & (1 << PD2)) == 0) { //PD2 nhấn, rắn di chuyển sang PHẢI
        new_dir_x = 0;
        new_dir_y = 1;
    }
    else if ((PIND & (1 << PD3)) == 0) { //PD3 nhấn, rắn di chuyển xuống DƯỚI
        new_dir_x = 1;
        new_dir_y = 0;
    }
    else {
        return; // Không có nút nào được nhấn
    }
    
    // Ngăn rắn quay đầu 180 độ 
	// Ví dụ rắn đang đi sang PHẢI, nhấn TRÁI, nếu k ktra thì rắn tự đâm đầu vào mình -> game over
    // Vòng lặp: kiểm tra hướng đi có ĐỐI DIỆN hướng cũ hay kh?
    // Có: BỎ QUA khỏi làm cái gì
    // Không: CẬP NHẬT biến dir_ mới
    if (new_dir_x != -dir_x || new_dir_y != -dir_y) {
        dir_x = new_dir_x;
        dir_y = new_dir_y;
    }
}


