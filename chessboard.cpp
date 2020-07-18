#include "chessboard.h"

void chessboard::setup() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j].chessType = 0;
			// C1 �� F1 ����Ϊ�ҷ���Դ����
			if (j > 1 && j < 6 && i == 0) board[i][j].origin = 1;
			// C8 �� F8 ����Ϊ�෽��Դ����
			else if (j > 1 && j < 6 && i == 7) board[i][j].origin = -1;
			// ��������Ϊ��ͨ����;
			else board[i][j].origin = 0;
		}	
	}

	// D2,E2����Ϊ��Ҷ
	board[1][3].chessType = 1;
	board[1][4].chessType = 1;
	// D7,E8����Ϊ��Ҷ
	board[6][3].chessType = -1;
	board[6][4].chessType = -1;

}

bool chessboard::scan_board(int x, int y, int camp, int type) {

	if (x < 0 || y < 0 || x>7 || y>7) return false;
	/*
		campΪ���ӷ�����Ӫ����ʱ��x��y��Ӧ������Ϊ���ƶ�������
		��x,y)���ڵ�chessType����˸ø��е����ӣ����ӣ�0����Ҷ��1����֦��2�����ɣ�3���������ű�ʾ��Ӫ
		���camp��chessType�ĳ˻�����ͬʱ��ʾ�������Ƿ����ڼ����Լ���������
	*/
	int t = board[x][y].chessType;
	int r = t * camp;
	if (type == 1 && ( r == 1 || r == 2 || r == 3)) return true;
	else if (type == 2 && r == 2) return true;
	else return false;
}


bool chessboard::step(int x, int y, int chessType) {
	//���ڹ��򣬲��ܽ��������ڼ����ĸ�Դ��������ֱ�ӷ���false
	//ֻ�е�chesstypeΪ��ʱ�����Ӳ�Ϊ��
	if ( board[x][y].origin * chessType > 0 || board[x][y].chessType != 0)
		return false;

	int camp;
	//camp��ʾ��Ӫ��1Ϊ�ҷ���-1Ϊ�෽
	if (chessType > 0) camp = 1;
	else camp = -1;

	//˳��ɨ�������ӵ�Ϊ���ĵ� 5X3 ��������������ѷ���Ӧ����������ʸ�
	int raw[3] = { -1,0,1 };
	int col[5] = { -2,-1,0,1,2 };
	int res = false;
	for (int i : raw) {
		for (int j : col) {
			if (i && j == 0) continue;
			if (j == 2 || j == -2) 
				res = scan_board(x + i, y + j,camp, 2);
			else
				res = scan_board(x + i, y + j,camp, 1);
			if (res) break;
		}
	}
	if (res) {
		if (chessType > 0)
			num_Gray++;
		else
			num_Green++;
		push(x - 1, y, 'w', camp);
		push(x + 1, y, 's', camp);
		push(x, y - 1, 'a', camp);
		push(x, y + 1, 'd', camp);
	}
	else return false;

}

void chessboard::push(int x, int y, char dir, int camp) {
	//ĳ��ֵԽ��˵���������ڱ߽��ϣ����Ӧ������Ҫ�ƶ�
	if (x < 0 || y < 0 || x>7 || y>7)
		return;
	/*
		campΪ���ӷ�����Ӫ����ʱ��x��y��Ӧ������Ϊ���ƶ�������
		��x,y)���ڵ�chessType����˸ø��е����ӣ����ӣ�0����Ҷ��1����֦��2�����ɣ�3���������ű�ʾ��Ӫ
		���camp��chessType�ĳ˻����Ա�ʾ�������Ƿ����ڼ���
		�������ӣ� �� = 0���ͼ������Ӳ��ܱ��ƶ��� �� > 0 )
		����ֻ�е������Ϊ����ʱ����ʾ�ø�����Ϊ�з����ӣ����Ա��ƶ�
		���ǣ��ɣ�3���ڹ����ϲ��ܱ��ƶ������ԣ��� �� == -1 �� -2 ʱ����ִ���ƶ�����
		dir��ʾ���ƶ��ķ���
	
	*/
	if (board[x][y].chessType * camp == -1 || board[x][y].chessType * camp == -2) {
		//x1,y1������ʱ���ɨ��λ��
		int x1 = x;
		int y1 = y;

		switch (dir)
		{
		case 'w'://��
			//�߽������޷����ƶ�������ж�����Ϊ 0 < x1 < 7, 0 < y1 <8
			while (x1 > 0) {
				// t Ϊ���·��жϴ������ʱ��������ʾɨ��λ�õ�chessType
				int t = board[x1][y1].chessType;

				//���ݹ��򣬵ط��ĸ� �� �ҷ����� �ᵼ�¸��ж��޷��ƶ�
				if (t * camp == -3 || t * camp > 0) break;
				//ֻ�е�ɨ����һ���հ�����ʱ������������ȫ����հ״��ƶ�
				//��Ϊ�ǵ����ƶ����Բ���Ҫ����������ǰһ��ֵ����
				else if (t * camp == 0) {
					while (x1 < x) {
						board[x1][y1].chessType = board[x + 1][y1].chessType;
						x1++;
					}
					board[x1][y1].chessType = 0;
					break;
				}
				x1--;
			}
			break;

		case 's'://��
			while (x1 < 7) {
				int t = board[x1][y1].chessType;
				if (t * camp == -3 || t * camp > 0) break;
				else if (t * camp == 0) {
					while (x1 > x) {
						board[x1][y1].chessType = board[x - 1][y1].chessType;
						x1--;
					}
					board[x1][y1].chessType = 0;
					break;
				}
				x1++;
			}
			break;

		case 'a'://��
			while (y1 > 0) {
				int t = board[x1][y1].chessType;
				if (t * camp == -3 || t * camp > 0) break;
				else if (t * camp == 0) {
					while (y1 < y) {
						board[x1][y1].chessType = board[x1][y1 + 1].chessType;
						y1++;
					}
					board[x1][y1].chessType = 0;
					break;
				}
				y1--;
			}
			break;

		case 'd'://��
			while (y1 < 7) {
				int t = board[x1][y1].chessType;
				if (t * camp == -3 || t * camp > 0) break;
				else if (t * camp == 0) {
					while (y1 < y) {
						board[x1][y1].chessType = board[x1][y1 - 1].chessType;
						y1--;
					}
					board[x1][y1].chessType = 0;
					break;
				}
				y1++;
				break;
			}
		}
	}
	else return;
}