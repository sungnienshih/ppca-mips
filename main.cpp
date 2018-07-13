#include<iostream>
#include<fstream>
#include"lexer.hpp"
#include"algo.hpp"
#include"parser.hpp"
#include<vector>
#include<map>
#include<algorithm>
#include <cstring>

using namespace std;

vector<line> code;
char memory[5000002] = { 0 };
int registers[36] = { 0 };
map<string, int> labels;
map<string, int> pointers;
vector<int> labval;
vector<int> ptrval;
int heapptr = 0;
int state = 0;
int cur = 1;
int main(int argc, char *argv[])
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	line xx;
	code.push_back(xx);
	registers[29] = 5000002;
	int runpos = 1, y = 1;
	ifstream fs(argv[1]);
	while (1)
	{
		y = readline(fs, state);
		if (y == 0) break;
		if (code[cur].type == MAIN)
		{
			runpos = cur;
		}
		if (code[cur].type == DATA) state = 0;
		if (code[cur].type == TEXT) state = 1;
		cur++;
	}
	int end = cur;
	cur = runpos;
	while (cur < end)
	{
		if (code[cur].type == ADD)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = registers[d1] + registers[d2];
			if (op == 0) registers[d] = registers[d1] + d2;
		}
		if (code[cur].type == ADDU)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = (unsigned int)(registers[d1] + registers[d2]);
			if (op == 0) registers[d] = (unsigned int)(registers[d1] + d2);
		}
		if (code[cur].type == ADDIU)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = (unsigned int)(registers[d1] + registers[d2]);
			if (op == 0) registers[d] = (unsigned int)(registers[d1] + d2);
		}
		if (code[cur].type == SUB)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = registers[d1] - registers[d2];
			if (op == 0) registers[d] = registers[d1] - d2;
		}
		if (code[cur].type == SUBU)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = (unsigned int)(registers[d1] - registers[d2]);
			if (op == 0) registers[d] = (unsigned int)(registers[d1] - d2);
		}
		if (code[cur].type == MUL)
		{
			if (code[cur].cont.size() == 4)
			{
				int op = code[cur].cont[0];
				int d = code[cur].cont[1];
				int d1 = code[cur].cont[2];
				int d2 = code[cur].cont[3];
				if (op == 1) registers[d] = registers[d1] * registers[d2];
				if (op == 0) registers[d] = registers[d1] * d2;
			}
			else
			{
				int op = code[cur].cont[0];
				int d1 = code[cur].cont[1];
				int d2 = code[cur].cont[2];
				if (op == 1)
				{
					registers[33] = (registers[d1] * registers[d2]) % 4294967296;
					registers[32] = (registers[d1] * registers[d2]) / 4294967296;
				}
				if (op == 0)
				{
					registers[33] = (registers[d1] * d2) % 4294967296;
					registers[32] = (registers[d1] * d2) / 4294967296;
				}
			}
		}
		if (code[cur].type == MULU)
		{
			if (code[cur].cont.size() == 4)
			{
				int op = code[cur].cont[0];
				int d = code[cur].cont[1];
				int d1 = code[cur].cont[2];
				int d2 = code[cur].cont[3];
				if (op == 1) registers[d] = (unsigned int)(registers[d1] * registers[d2]);
				if (op == 0) registers[d] = (unsigned int)(registers[d1] * d2);
			}
			else
			{
				int op = code[cur].cont[0];
				int d1 = code[cur].cont[1];
				int d2 = code[cur].cont[2];
				if (op == 1)
				{
					registers[33] = (registers[d1] * registers[d2]) % 4294967296;
					registers[32] = (registers[d1] * registers[d2]) / 4294967296;
				}
				if (op == 0)
				{
					registers[33] = (registers[d1] * d2) % 4294967296;
					registers[32] = (registers[d1] * d2) / 4294967296;
				}
			}
		}
		if (code[cur].type == DIV)
		{
			if (code[cur].cont.size() == 4)
			{
				int op = code[cur].cont[0];
				int d = code[cur].cont[1];
				int d1 = code[cur].cont[2];
				int d2 = code[cur].cont[3];
				if (op == 1) registers[d] = registers[d1] / registers[d2];
				if (op == 0) registers[d] = registers[d1] / d2;
			}
			else
			{
				int op = code[cur].cont[0];
				int d1 = code[cur].cont[1];
				int d2 = code[cur].cont[2];
				if (op == 1)
				{
					registers[33] = (registers[d1] / registers[d2]);
					registers[32] = (registers[d1] % registers[d2]);
				}
				if (op == 0)
				{
					registers[33] = (registers[d1] / d2);
					registers[32] = (registers[d1] % d2);
				}
			}
		}
		if (code[cur].type == DIVU)
		{
			if (code[cur].cont.size() == 4)
			{
				int op = code[cur].cont[0];
				int d = code[cur].cont[1];
				int d1 = code[cur].cont[2];
				int d2 = code[cur].cont[3];
				if (op == 1) registers[d] = (unsigned int)(registers[d1] / registers[d2]);
				if (op == 0) registers[d] = (unsigned int)(registers[d1] / d2);
			}
			else
			{
				int op = code[cur].cont[0];
				int d1 = code[cur].cont[1];
				int d2 = code[cur].cont[2];
				if (op == 1)
				{
					registers[33] = (unsigned int)(registers[d1] % registers[d2]);
					registers[32] = (unsigned int)(registers[d1] / registers[d2]);
				}
				if (op == 0)
				{
					registers[33] = (unsigned int)(registers[d1] % d2);
					registers[32] = (unsigned int)(registers[d1] / d2);
				}
			}
		}
		if (code[cur].type == XOR)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = registers[d1] ^ registers[d2];
			if (op == 0) registers[d] = registers[d1] ^ d2;
		}
		if (code[cur].type == XORU)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = (unsigned int)(registers[d1] ^ registers[d2]);
			if (op == 0) registers[d] = (unsigned int)(registers[d1] ^  d2);
		}
		if (code[cur].type == NEG)
		{
			int d = code[cur].cont[0];
			int d1 = code[cur].cont[1];
			registers[d] = -registers[d1];
		}
		if (code[cur].type == NEGU)
		{
			int d = code[cur].cont[0];
			int d1 = code[cur].cont[1];
			registers[d] = (unsigned int)(~registers[d1]);
		}
		if (code[cur].type == REM)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = registers[d1] % registers[d2];
			if (op == 0) registers[d] = registers[d1] % d2;
		}
		if (code[cur].type == REMU)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = (unsigned int)(registers[d1] % registers[d2]);
			if (op == 0) registers[d] = (unsigned int)(registers[d1] % d2);
		}
		if (code[cur].type == LI)
		{
			int d = code[cur].cont[0];
			int imm = code[cur].cont[1];
			registers[d] = imm;
		}
		if (code[cur].type == SEQ)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = (registers[d1] == registers[d2]);
			if (op == 0) registers[d] = (registers[d1] == d2);
		}
		if (code[cur].type == SGE)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = (registers[d1] >= registers[d2]);
			if (op == 0) registers[d] = (registers[d1] >= d2);
		}
		if (code[cur].type == SGT)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = (registers[d1] > registers[d2]);
			if (op == 0) registers[d] = (registers[d1] > d2);
		}
		if (code[cur].type == SLE)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = (registers[d1] <= registers[d2]);
			if (op == 0) registers[d] = (registers[d1] <= d2);
		}
		if (code[cur].type == SLT)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = (registers[d1] < registers[d2]);
			if (op == 0) registers[d] = (registers[d1] < d2);
		}
		if (code[cur].type == SNE)
		{
			int op = code[cur].cont[0];
			int d = code[cur].cont[1];
			int d1 = code[cur].cont[2];
			int d2 = code[cur].cont[3];
			if (op == 1) registers[d] = (registers[d1] != registers[d2]);
			if (op == 0) registers[d] = (registers[d1] != d2);
		}
		if (code[cur].type == LA)
		{
			int d = code[cur].cont[0];
			int add;
			if (code[cur].cont.size() == 3)
			{
				int x1 = code[cur].cont[1];
				int x2 = code[cur].cont[2];
				add = registers[x2] + x1;
			}
			else
			{
				add = ptrval[code[cur].cont[1]];
			}
			registers[d] = add;
		}
		if (code[cur].type == LB)
		{
			int d = code[cur].cont[0];
			int add;
			if (code[cur].cont.size() == 3)
			{
				int x1 = code[cur].cont[1];
				int x2 = code[cur].cont[2];
				add = registers[x2] + x1;
			}
			else
			{
				add = ptrval[code[cur].cont[1]];
			}
			registers[d] = 0;
			memcpy(&registers[d], &memory[add], 1);
		}
		if (code[cur].type == LH)
		{
			int d = code[cur].cont[0];
			int add;
			if (code[cur].cont.size() == 3)
			{
				int x1 = code[cur].cont[1];
				int x2 = code[cur].cont[2];
				add = registers[x2] + x1;
			}
			else
			{
				add = ptrval[code[cur].cont[1]];
			}
			registers[d] = 0;
			memcpy(&registers[d], &memory[add], 2);
		}
		if (code[cur].type == LW)
		{
			int d = code[cur].cont[0];
			int add;
			if (code[cur].cont.size() == 3)
			{
				int x1 = code[cur].cont[1];
				int x2 = code[cur].cont[2];
				add = registers[x2] + x1;
			}
			else
			{
				add = ptrval[code[cur].cont[1]];
			}
			registers[d] = 0;
			memcpy(&registers[d], &memory[add], 4);
		}
		if (code[cur].type == SB)
		{
			int d = code[cur].cont[0];
			int add;
			if (code[cur].cont.size() == 3)
			{
				int x1 = code[cur].cont[1];
				int x2 = code[cur].cont[2];
				add = registers[x2] + x1;
			}
			else
			{
				add = ptrval[code[cur].cont[1]];
			}
			memcpy(&memory[add], &registers[d], 1);
		}
		if (code[cur].type == SH)
		{
			int d = code[cur].cont[0];
			int add;
			if (code[cur].cont.size() == 3)
			{
				int x1 = code[cur].cont[1];
				int x2 = code[cur].cont[2];
				add = registers[x2] + x1;
			}
			else
			{
				add = ptrval[code[cur].cont[1]];
			}
			memcpy(&memory[add], &registers[d], 2);
		}
		if (code[cur].type == SW)
		{
			int d = code[cur].cont[0];
			int add;
			if (code[cur].cont.size() == 3)
			{
				int x1 = code[cur].cont[1];
				int x2 = code[cur].cont[2];
				add = registers[x2] + x1;
			}
			else
			{
				add = ptrval[code[cur].cont[1]];
			}
			memcpy(&memory[add], &registers[d], 4);
		}
		if (code[cur].type == MOVE)
		{
			int d = code[cur].cont[0];
			int d1 = code[cur].cont[1];
			registers[d] = registers[d1];
		}
		if (code[cur].type == MFHI)
		{
			int d = code[cur].cont[0];
			registers[d] = registers[32];
		}
		if (code[cur].type == MFLO)
		{
			int d = code[cur].cont[0];
			registers[d] = registers[33];
		}
		if (code[cur].type == SYSCALL)
		{
			int com = registers[2];
			int ret = syscall(com);
			if (ret == 0) break;
		}
		if (code[cur].type == B)
		{
			int lab = code[cur].cont[0];
			int pos = labval[lab];
			cur = pos;
			continue;
		}
		if (code[cur].type == BEQ)
		{
			int d1 = code[cur].cont[1];
			int d2 = code[cur].cont[2];
			bool f = false;
			if (code[cur].cont[0] == 1)
			{
				f = (registers[d1] == registers[d2]);
			}
			if (code[cur].cont[0] == 0)
			{
				f = (registers[d1] == d2);
			}
			if (f)
			{
				int lab = code[cur].cont[3];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == BNE)
		{
			int d1 = code[cur].cont[1];
			int d2 = code[cur].cont[2];
			bool f = false;
			if (code[cur].cont[0] == 1)
			{
				f = (registers[d1] != registers[d2]);
			}
			if (code[cur].cont[0] == 0)
			{
				f = (registers[d1] != d2);
			}
			if (f)
			{
				int lab = code[cur].cont[3];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == BGE)
		{
			int d1 = code[cur].cont[1];
			int d2 = code[cur].cont[2];
			bool f = false;
			if (code[cur].cont[0] == 1)
			{
				f = (registers[d1] >= registers[d2]);
			}
			if (code[cur].cont[0] == 0)
			{
				f = (registers[d1] >= d2);
			}
			if (f)
			{
				int lab = code[cur].cont[3];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == BLE)
		{
			int d1 = code[cur].cont[1];
			int d2 = code[cur].cont[2];
			bool f = false;
			if (code[cur].cont[0] == 1)
			{
				f = (registers[d1] <= registers[d2]);
			}
			if (code[cur].cont[0] == 0)
			{
				f = (registers[d1] <= d2);
			}
			if (f)
			{
				int lab = code[cur].cont[3];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == BGT)
		{
			int d1 = code[cur].cont[1];
			int d2 = code[cur].cont[2];
			bool f = false;
			if (code[cur].cont[0] == 1)
			{
				f = (registers[d1] > registers[d2]);
			}
			if (code[cur].cont[0] == 0)
			{
				f = (registers[d1] > d2);
			}
			if (f)
			{
				int lab = code[cur].cont[3];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == BLT)
		{
			int d1 = code[cur].cont[1];
			int d2 = code[cur].cont[2];
			bool f = false;
			if (code[cur].cont[0] == 1)
			{
				f = (registers[d1] < registers[d2]);
			}
			if (code[cur].cont[0] == 0)
			{
				f = (registers[d1] < d2);
			}
			if (f)
			{
				int lab = code[cur].cont[3];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == BEQZ)
		{
			int d = code[cur].cont[0];
			int r = registers[d];
			if (r == 0)
			{
				int lab = code[cur].cont[1];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == BNEZ)
		{
			int d = code[cur].cont[0];
			int r = registers[d];
			if (r != 0)
			{
				int lab = code[cur].cont[1];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == BLEZ)
		{
			int d = code[cur].cont[0];
			int r = registers[d];
			if (r <= 0)
			{
				int lab = code[cur].cont[1];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == BGEZ)
		{
			int d = code[cur].cont[0];
			int r = registers[d];
			if (r >= 0)
			{
				int lab = code[cur].cont[1];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == BGTZ)
		{
			int d = code[cur].cont[0];
			int r = registers[d];
			if (r > 0)
			{
				int lab = code[cur].cont[1];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == BLTZ)
		{
			int d = code[cur].cont[0];
			int r = registers[d];
			if (r < 0)
			{
				int lab = code[cur].cont[1];
				int pos = labval[lab];
				cur = pos;
				continue;
			}
		}
		if (code[cur].type == J)
		{
			int lab = code[cur].cont[0];
			int pos = labval[lab];
			cur = pos;
			continue;
		}
		if (code[cur].type == JAL)
		{
			registers[31] = cur + 1;
			int lab = code[cur].cont[0];
			int pos = labval[lab];
			cur = pos;
			continue;
		}
		if (code[cur].type == JR)
		{
			int d = code[cur].cont[0];
			int pos = registers[d];
			cur = pos;
			continue;
		}
		if (code[cur].type == JALR)
		{
			registers[31] = cur + 1;
			int d = code[cur].cont[0];
			int pos = registers[d];
			cur = pos;
			continue;
		}
		cur++;
	}
	fs.close();
	return 0;
}

