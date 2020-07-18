#pragma once
struct cell
{
	//�������ͣ�1 2 3Ϊ�����������࣬������ʾ��Ӫ,��Ϊ�ҷ�����Ϊ�෽��
	int chessType; 
	//�Ƿ�Ϊ��Դ����0���ǣ�1Ϊ�ҷ���Դ��-1Ϊ�෽��Դ
	int origin;
};
class chessboard
{
private:
	cell board[8][8];

	//�ҷ�ʣ��������
	int num_Gray;

	//�෽ʣ��������
	int num_Green;

	//ɨ����Χ�Ƿ��п����ʸ�������,type����Ϊɨ�跽ʽ��1Ϊɨ����Χ�ĸ���Ҷ��2Ϊɨ����Χ��֦�������û���򷵻�false
	bool scan_board(int x, int y, int camp, int type);

	//���ӳɹ����ƶ���Χ����
	void push(int x, int y, char dir, int camp);
public:
	//���̳�ʼ��
	void setup();

	//�������ӣ�x��yΪ�������꣬chesstypeΪ�������ͣ���������Ӫ����ΧֵΪ�����Ƿ���Ч
	bool step(int x, int y, int chessType);
	
	//�ж���Ϸ�Ƿ����������ֵΪʤ������0δδ����
	int judge();
};

