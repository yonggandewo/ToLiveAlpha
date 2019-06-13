#include<windows.h>
#include<iostream>
#include<conio.h>
#include<fstream>
#include<random>
#include<vector>
#include<ctime>
using namespace std;
const string aname[5]={"木","石","铁","钻","金"},bname[5]={"镐","剑","斧","铲","锄"},cname[10]={"土地","耕地","小麦","面包","生肉","熟肉","煤炭","铁矿","金矿","神秘矿物"};
long long matter[50],level,money,healthy;
const long long thingtime[5]={10,20,50,100,5},need[5][2]={{2,3},{1,2},{2,3},{2,1},{2,2}};
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
HWND hWnd=GetConsoleWindow();
string user,file;
bool have;
int Rand(){
	std::mt19937 mt(rand());
	return mt()%RAND_MAX;
}
void color(int f,int b){
	SetConsoleTextAttribute(hOut,f*16+b);
}
string ll2str(long long x){
	string ans="";
	while(x){
		ans=(char)(x%10+'0')+ans;
		x/=10;
	}
	return ans;
}
void out(string wd){
	for(long long i=0;i<wd.size();i++){
		putchar(wd[i]);
		Sleep(Rand()%60+20);
	}
}
void say(string name,string wd){
	cout<<"【"<<name<<"】：";
	out(wd);
}
void lb(long long tot){
	for(long long i=0;i<tot;i++)putchar(' ');
}
void wline(){
	color(0,8);
	for(long long i=0;i<41;i++)putchar('-');
}
string randword(const vector<string>&wdlist){
	return wdlist[Rand()%wdlist.size()];
}
string itemname(long long code){
	if(code<5)return aname[code];
	if(code>29)return cname[code-30];
	return aname[code%5]+bname[code/5-1];
}
long long priceof(long long k){
	if(k<5||k>29)switch(k){
		case 0:return 10;
		case 1:return 20;
		case 2:return 75;
		case 3:return 150;
		case 4:return 175;
		case 30:return 3;
		case 31:return 7;
		case 32:return 10;
		case 33:return 15;
		case 34:return 10;
		case 35:return 20;
		case 36:return 25;
		case 37:return 50;
		case 38:return 125;
		case 39:return 500;
	}
	return 10*need[k/5-1][0]+priceof(k%5)*need[k/5-1][0];
}
void setwindow(short r,short c){
	COORD size={c,100};
	SMALL_RECT rc;
	RECT rc2;
	rc.Right=c-1;
	rc.Bottom=r-1;
	rc.Left=rc.Top=0;
	SetConsoleTitle("ToLive");
	SetConsoleWindowInfo(hOut,true,&rc);
	SetConsoleScreenBufferSize(hOut,size);
    GetWindowRect(hWnd, &rc2);
    SetWindowLongPtr(hWnd,GWL_STYLE,GetWindowLong(hWnd,GWL_STYLE)&~WS_THICKFRAME&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX);
    SetWindowPos(hWnd,NULL,rc2.left,rc2.top,rc2.right-rc2.left,rc2.bottom-rc2.top,NULL);
}
void HideCursor(){
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut,&cci);
	cci.bVisible=false;
	SetConsoleCursorInfo(hOut,&cci);
}
bool SetCursorPosition(short x,short y){
    return SetConsoleCursorPosition(hOut,(COORD){y,x});
}
COORD GetCursorPosition(){
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    GetConsoleScreenBufferInfo(hOut,&sbi);
    return sbi.dwCursorPosition;
}
void _set(int id,int line,int col1,int col2,string st){
    SetCursorPosition(line,0);
    color(col1/16,col1%16);
    cout<<id<<". "<<st<<endl;
    color(col2/16,col2%16);
}
int choose(const vector<string>&op,int co=240,int uc=15,int sel=0){
	COORD cpos=GetCursorPosition();
	int len=op.size(),s1=cpos.Y,s2=s1,cur=sel;
	vector<int>pos;
	char ch;
	for(int i=0;i<len;i++){
		pos.push_back(s1);
		if(i==sel)SetConsoleTextAttribute(hOut,co);
		cout<<i<<". "<<op[i]<<endl;
		if(i==sel)SetConsoleTextAttribute(hOut,uc);
		s1++;
	}
	while((ch=_getch())!='\r'){
		if(ch==72||ch=='W'||ch=='w'){
			_set(cur,s2+cur,uc,co,op[cur]);
			if(!cur)cur=len-1;
			else cur--;
			_set(cur,s2+cur,co,uc,op[cur]);
		}else if(ch==80||ch=='S'||ch=='s'){
			_set(cur,s2+cur,uc,co,op[cur]);
			if(cur==len-1)cur=0;
			else cur++;
			_set(cur,s2+cur,co,uc,op[cur]);
		}else if(isdigit(ch)){
			int x=ch-'0';
			if(x>=len)continue;
			if(x!=cur){
				_set(cur,s2+cur,uc,co,op[cur]);
				cur=x;
				_set(cur,s2+cur,co,uc,op[cur]);
			}
		}
	}
	SetCursorPosition(cpos.Y+len,0);
	return cur;
}
int main(){
	srand(time(NULL));
	HideCursor();
	setwindow(27,41);
	SetConsoleOutputCP(936);
	color(0,15);
	puts("读档中......");
	ifstream in("data.sgr");
	if(!in.is_open()){
		out("对不起,读档时发生错误,请确认你的存档正常");
		getch();
		in.close();
		return 0;
	}
	getline(in,file);
	in>>level>>money>>healthy;
	for(long long i=0;i<40;i++)in>>matter[i];
	system("cls");
	lb(15);
	out("ToLive v1.0.2\n");
	wline();
	color(0,15);
	say("YHX","我好像在哪里见过你...\n");
	say("YHX","我该怎么称呼你?\n");
	cout<<"【你】：";
	getline(cin,user);
	system("cls");
	if(user!=file){
		say("YHX","原来我是第一次遇到你!\n");
		level=0;
		money=1000;
		healthy=100;
		memset(matter,0,sizeof(matter));
	}else say("YHX","啊,是你啊!\n");
	say("YHX","加油,继续前进!\n");
	getch();
	while(healthy>0){
		level++;
		system("cls");
		color(0,12);
		lb(15);
		puts("ToLive v1.0.2");
		wline();
		color(0,14);
		cout<<user<<"\n金币："<<money<<"\n生命："<<healthy<<"\n";
		wline();
		color(0,11);
		cout<<"第"<<level<<"天\n";
		puts("你的背包：");
		have=0;
		for(long long i=0;i<5;i++)if(matter[i]){
			cout<<aname[i]<<"  x"<<matter[i]<<endl;
			have=1;
		}
		for(long long i=5;i<30;i++)if(matter[i]){
			cout<<aname[i%5]<<bname[i/5-1]<<'x'<<matter[i]<<endl;
			have=1;
		}
		for(long long i=30;i<40;i++)if(matter[i]){
			cout<<cname[i-30]<<'x'<<matter[i]<<endl;
			have=1;
		}
		if(!have)puts("空");
		wline();
		vector<string>act={"发呆","采木","采石","挖矿","工具","交易","打怪","种地","烹饪","熔炼"};
		switch(choose(act)){
			case 0:{
				say("YHX","发呆成功!回复1点生命\n");
				say("你",randword(vector<string>({"...","这...","话说发呆还有成功不成功的?"})));
				healthy++;
				getch();
				break;
			}
			case 1:{
				say("YHX","你要用什么采集木头?\n");
				long long cut=choose(vector<string>({"手!","木斧","石斧","铁斧","钻斧","金斧"}));
				if(!cut){
					say("YHX","很好!你采到了3块木头!但有点痛...");
					healthy-=3;
					matter[0]+=3;
				}else{
					if(matter[14+cut]){
						say("YHX","真不错,你用斧头采到了木头!");
						matter[14+cut]--;
						matter[0]+=thingtime[cut-1];
					}else{
						say("YHX","非常遗憾.你没有这种斧头.\n");
						say("你",randword(vector<string>({"What?","What!","不!","..."})));
					}
				}
				getch();
				break;
			}
			case 2:{
				say("YHX","你要用什么采集石头?\n");
				long long cut=choose(vector<string>({"木镐","石镐","铁镐","钻镐","金镐"}));
				if(matter[5+cut]){
					say("YHX","真不错,你用镐子采到了石头!");
					matter[5+cut]--;
					matter[1]+=thingtime[cut];
				}else{
					say("YHX","非常遗憾.你没有这种镐子.\n");
					say("你",randword(vector<string>({"What?","What!","不!","..."})));
				}
				getch();
				break;
			}
			case 3:{
				if(Rand()%2){
					if(Rand()%2){
						say("YHX","真不幸!你只找到了石头.\n");
						say("YHX","你要用什么采集石头?\n");
						long long cut=choose(vector<string>({"木镐","石镐","铁镐","钻镐","金镐"}));
						if(matter[5+cut]){
							say("YHX","你用镐子采到了石头!");
							matter[5+cut]--;
							matter[1]+=thingtime[cut];
						}else{
							say("YHX","非常遗憾.你没有这种镐子.\n");
							say("你",randword(vector<string>({"What?","What!","不!","..."})));
						}
					}else{
						if(Rand()%2){
							say("YHX","你找到了煤矿!\n");
							say("YHX","你要用什么采集煤矿?\n");
							long long cut=choose(vector<string>({"木镐","石镐","铁镐","钻镐","金镐"}));
							if(matter[5+cut]){
								say("YHX","你用镐子采到了煤矿!");
								matter[5+cut]--;
								matter[36]+=thingtime[cut];
							}else{
								say("YHX","非常遗憾.你没有这种镐子.\n");
								say("你",randword(vector<string>({"What?","What!","不!","..."})));
							}
						}else if(Rand()%2){
							say("YHX","你找到了铁矿!\n");
							say("YHX","你要用什么采集铁矿?\n");
							long long cut=choose(vector<string>({"石镐","铁镐","钻镐","金镐"}));
							if(matter[6+cut]){
								say("YHX","你用镐子采到了铁矿!");
								matter[6+cut]--;
								matter[37]+=thingtime[cut]/2;
							}else{
								say("YHX","非常遗憾.你没有这种镐子.\n");
								say("你",randword(vector<string>({"What?","What!","不!","..."})));
							}
						}else{
							if(!Rand()%3){
								say("YHX","你找到了钻石!\n");
								say("YHX","你要用什么采集钻石?\n");
								long long cut=choose(vector<string>({"铁镐","钻镐"}));
								if(matter[7+cut]){
									say("YHX","你用镐子采到了钻石!");
									matter[7+cut]--;
									matter[3]+=thingtime[cut]/5;
								}else{
									say("YHX","非常遗憾.你没有这种镐子.\n");
									say("你",randword(vector<string>({"What?","What!","不!","..."})));
								}
							}else if(Rand()%2){
								say("YHX","你找到了黄金!\n");
								say("YHX","你要用什么采集黄金?\n");
								long long cut=choose(vector<string>({"铁镐","钻镐","金镐"}));
								if(matter[7+cut]){
									say("YHX","你用镐子采到了黄金!");
									matter[7+cut]--;
									matter[38]+=thingtime[cut]/5;
								}else{
									say("YHX","非常遗憾.你没有这种镐子.\n");
									say("你",randword(vector<string>({"What?","What!","不!","..."})));
								}
							}else{
								say("YHX","你找到了神秘矿物!\n");
								if(matter[8]){
									say("YHX","你用钻镐采到了神秘矿物!");
									matter[8]--;
									matter[39]+=1;
								}else{
									say("YHX","非常遗憾.你没有钻镐.\n");
									say("你",randword(vector<string>({"What?","What!","不!","..."})));
								}
							}
						}
					}
				}else{
					long long hurt;
					say("YHX","你遇到了怪物!\n");
					if(choose(vector<string>({"战斗","逃跑"}))){
						hurt=5+Rand()%10;
						healthy-=hurt;
						say("YHX","你逃走了,但还是受到了");
						cout<<hurt;
						out("点伤害!");
					}else{
						say("YHX","你要用什么攻击怪物?\n");
						long long kind=choose(vector<string>({"手!","木剑","石剑","铁剑","钻剑","金剑"}));
						if(!kind){
							hurt=50+Rand()%10;
							healthy-=hurt;
							matter[34]++;
							say("YHX","你打倒了怪物,并受到了");
							cout<<hurt;
							out("点伤害!\n");
							say("YHX","你获得了生肉");
						}else{
							if(matter[kind+9]){
								hurt=100/thingtime[kind-1]+Rand()%10;
								matter[kind+9]--;
								healthy-=hurt;
								matter[34]++;
								say("YHX","你打倒了怪物,并受到了");
								cout<<hurt;
								out("点伤害,\n");
								say("YHX","你获得了生肉");
							}else{
								hurt=50+Rand()%10;
								healthy-=hurt;
								say("YHX","非常遗憾.你没有这种剑.\n");
								say("YHX","你受到了");
								cout<<hurt;
								out("点伤害!\n");
								say("你",randword(vector<string>({"What?","What!","不!","..."})));
							}
						}
					}
				}
				getch();
				break;
			}
			case 4:{
				long long from,to;
				say("YHX","你要用什么材料?\n");
				from=choose(vector<string>({"木","石","铁","钻","金"}));
				say("YHX","你要造什么工具?\n");
				to=choose(vector<string>({"镐","剑","斧","铲","锄"}));
				if(from){
					if(matter[0]<need[to][0]||matter[from]<need[to][1]){
						say("YHX","非常遗憾.你没有足够的材料.\n");
						say("你",randword(vector<string>({"What?","What!","不!","..."})));
					}else{
						matter[0]-=need[to][0];
						matter[from]-=need[to][1];
						matter[to*5+from+5]++;
						say("YHX","成功造出!");
					}
				}else{
					if(matter[0]<need[to][0]+need[to][1]){
						say("YHX","非常遗憾.你没有足够的材料.\n");
						say("你",randword(vector<string>({"What?","What!","不!","..."})));
					}else{
						matter[0]-=need[to][0]+need[to][1];
						matter[to*5+5]++;
						say("YHX","成功造出!");
					}
				}
				getch();
				break;
			}
			case 5:{
				vector<string>itemnames;
				long long prices[10],codes[10];
				for(long long i=0;i<10;i++){
					codes[i]=Rand()%40;
					prices[i]=priceof(codes[i])+Rand()%20;
					itemnames.push_back(itemname(codes[i])+" "+ll2str(prices[i]));
				}
				say("YHX","你要买物品还是卖物品?\n");
				long long ti=choose(vector<string>({"买","卖"}));
				if(ti){
					say("YHX","你要卖什么?\n");
					long long w=choose(itemnames);
					if(matter[codes[w]]){
						matter[codes[w]]--;
						money+=prices[w];
						say("YHX","买卖成功!");
					}else{
						say("YHX","非常遗憾.你没有这种物品.\n");
						say("你",randword(vector<string>({"What?","What!","不!","..."})));
					}
				}else{
					say("YHX","你要买什么?\n");
					long long w=choose(itemnames);
					if(prices[w]<=money){
						matter[codes[w]]++;
						money-=prices[w];
						say("YHX","买卖成功!");
					}else{
						say("YHX","非常遗憾.你没有足够的钱.\n");
						say("你",randword(vector<string>({"What?","What!","不!","..."})));
					}
				}
				getch();
				break;
			}
			case 6:{
				long long hurt;
				say("YHX","你遇到了怪物!\n");
				if(choose(vector<string>({"战斗","逃跑"}))){
					hurt=5+Rand()%10;
					healthy-=hurt;
					say("YHX","你逃走了,但还是受到了");
					cout<<hurt;
					out("点伤害!");
				}else{
					say("YHX","你要用什么攻击怪物?\n");
					long long kind=choose(vector<string>({"手!","木剑","石剑","铁剑","钻剑","金剑"}));
					if(!kind){
						hurt=50+Rand()%10;
						healthy-=hurt;
						matter[34]++;
						say("YHX","你打倒了怪物,并受到了");
						cout<<hurt;
						out("点伤害!\n");
						say("YHX","你获得了生肉");
					}else{
						if(matter[kind+9]){
							hurt=100/thingtime[kind-1]+Rand()%10;
							matter[kind+9]--;
							healthy-=hurt;
							matter[34]++;
							say("YHX","你打倒了怪物,并受到了");
							cout<<hurt;
							out("点伤害,\n");
							say("YHX","你获得了生肉");
						}else{
							hurt=50+Rand()%10;
							healthy-=hurt;
							say("YHX","非常遗憾.你没有这种剑.\n");
							say("YHX","你受到了");
							cout<<hurt;
							out("点伤害!\n");
							say("你",randword(vector<string>({"What?","What!","不!","..."})));
					 	}
					}
				}
				break;
			}
			case 7:{
				say("YHX","你要干什么?\n");
				long long cho=choose(vector<string>({"挖土","耕地","种小麦"}));
				if(!cho){
					say("YHX","你要用什么挖土?\n");
					long long cut=choose(vector<string>({"手!","木铲","石铲","铁铲","钻铲","金铲"}));
					if(!cut){
						say("YHX","很好!你采到了3块土地!但有点痛...");
						matter[30]+=3;
						healthy-=3;
					}else{
						if(matter[19+cut]){
							say("YHX","真不错,你用铲子采到了土地!");
							matter[30]+=thingtime[cut-1];
							matter[19+cut]--;
						}else{
							say("YHX","非常遗憾.你没有这种铲子.\n");
							say("你",randword(vector<string>({"What?","What!","不!","..."})));
						}
					}
				}else if(cho==1){
					say("YHX","你要用什么耕土?\n");
					long long cut=choose(vector<string>({"木锄","石锄","铁锄","钻锄","金锄"}));
					if(matter[25+cut]){
						say("YHX","真不错,你用锄头锄出了耕地!");
						matter[31]+=min(thingtime[cut],matter[30]);
						matter[30]-=min(thingtime[cut],matter[30]);
						matter[25+cut]--;
					}else{
						say("YHX","非常遗憾.你没有这种锄头.\n");
						say("你",randword(vector<string>({"What?","What!","不!","..."})));
					}
				}else{
					long long num;
					say("YHX","你要种多少小麦?\n");
					cin>>num;
					if(matter[32]<num){
						say("YHX","非常遗憾,你没有这么多小麦.\n");
						say("你",randword(vector<string>({"What?","What!","不!","..."})));
					}else if(matter[31]<num){
						say("YHX","非常遗憾,你没有这么多耕地.\n");
						say("你",randword(vector<string>({"What?","What!","不!","..."})));
					}else{
						matter[32]+=2*num;
						matter[31]-=num;
						say("YHX","种小麦成功!");
					}
				}
				getch();
				break;
			}
			case 8:{
				say("YHX","煮吃的还是吃!\n");
				if(choose(vector<string>({"煮","吃"}))){
					say("YHX","你把能吃的全吃了!");
					healthy+=30*matter[33]+50*matter[35];
					matter[35]=0;
					matter[33]=0;
				}else{
					say("YHX","你把能煮的都煮了!");
					matter[35]+=matter[34]/3;
					matter[33]+=matter[32]/3;
					matter[32]%=3;
					matter[34]%=3;
				}
				getch();
				break;
			}
			case 9:{
				say("YHX","熔炼开始!\n");
				long long needed=matter[37]+matter[38]*2+matter[39]*5;
				if(matter[36]>=needed){
					matter[36]-=needed;
					matter[2]+=matter[37];
					matter[4]+=matter[38];
					switch(Rand()%4){
						case 0:{
							matter[36]+=matter[39]*10;
							break;
						}
						case 1:{
							matter[2]+=matter[39]*8;
							break;
						}
						case 2:{
							matter[3]+=matter[39]*6;
							break;
						}
						case 3:{
							matter[4]+=matter[39]*4;
							break;
						}
					}
					matter[37]=0;
					matter[38]=0;
					matter[39]=0;
					say("YHX","耶,熔炼成功!");
				}else{
					matter[36]=0;
					say("YHX","哎呀,火灭了,熔炼失败!");
				}
				getch();
				break;
			}
		}
		ofstream kout("data.sgr");
		kout<<user<<endl<<level<<' '<<money<<' '<<healthy<<endl;
		for(long long i=0;i<40;i++)kout<<matter[i]<<' ';
		kout.close();
		if(level%365==0){
			system("cls");
			color(0,12);
			lb(15);
			puts("ToLive v1.0.2");
			wline();
			color(0,14);
			cout<<user<<"\n金币："<<money<<"\n生命："<<healthy<<"\n";
			wline();
			color(0,11);
			cout<<"第"<<level<<"天\n";
			puts("你的背包：");
			have=0;
			for(long long i=0;i<5;i++)if(matter[i]){
				cout<<aname[i]<<"  x"<<matter[i]<<endl;
				have=1;
			}
			for(long long i=5;i<30;i++)if(matter[i]){
				cout<<aname[i%5]<<bname[i/5-1]<<'x'<<matter[i]<<endl;
				have=1;
			}
			for(long long i=30;i<36;i++)if(matter[i]){
				cout<<cname[i-30]<<'x'<<matter[i]<<endl;
				have=1;
			}
			if(!have)puts("空");
			wline();
			color(0,15);
			int get=Rand()%1000;
			money+=get;
			say("YHX","今天是你的生日!\n");
			say("YHX","你收到了的一份礼物.\n");
			say("YHX","你得到了");
			cout<<get;
			out("个金币!\n");
			say("你",randword(vector<string>({"哇!","真不错!","我喜欢!"})));
			getch();
		}
		if(level%50==0){
			system("cls");
			color(0,12);
			lb(15);
			puts("ToLive v1.0.2");
			wline();
			color(0,14);
			cout<<user<<"\n金币："<<money<<"\n生命："<<healthy<<"\n";
			wline();
			color(0,11);
			cout<<"第"<<level<<"天\n";
			puts("你的背包：");
			have=0;
			for(long long i=0;i<5;i++)if(matter[i]){
				cout<<aname[i]<<"  x"<<matter[i]<<endl;
				have=1;
			}
			for(long long i=5;i<30;i++)if(matter[i]){
				cout<<aname[i%5]<<bname[i/5-1]<<'x'<<matter[i]<<endl;
				have=1;
			}
			for(long long i=30;i<36;i++)if(matter[i]){
				cout<<cname[i-30]<<'x'<<matter[i]<<endl;
				have=1;
			}
			if(!have)puts("空");
			wline();
			long long hurt;
			color(0,15);
			say("YHX","怪物来袭!怎么办?\n");
			if(choose(vector<string>({"战斗","逃跑"}))){
				hurt=level+Rand()%10;
				healthy-=hurt;
				say("YHX","你逃走了,但还是受到了");
				cout<<hurt;
				out("点伤害!");
				getch();
			}else{
				say("YHX","你要用什么攻击怪物?\n");
				long long kind=choose(vector<string>({"手!","木剑","石剑","铁剑","钻剑","金剑"}));
				if(!kind){
					hurt=level*8/5+Rand()%10;
					healthy-=hurt;
					matter[34]+=3;
					say("YHX","你打倒了怪物,并受到了");
					cout<<hurt;
					out("点伤害!\n");
					say("YHX","你获得了生肉!");
					getch();
				}else{
					if(matter[kind+9]){
						hurt=level*20/thingtime[kind-1]+Rand()%10;
						matter[kind+9]--;
						healthy-=hurt;
						matter[34]++;
						say("YHX","你打倒了怪物,并受到了");
						cout<<hurt;
						out("点伤害,\n");
						say("YHX","你获得了生肉");
						getch();
					}else{
						hurt=level*7/5+Rand()%10;
						healthy-=hurt;
						say("YHX","非常遗憾.你没有这种剑.\n");
						say("YHX","你受到了");
						cout<<hurt;
						out("点伤害!\n");
						say("你",randword(vector<string>({"What?","What!","不!","..."})));
						getch();
					}
				}
			}
			if(healthy<=0)break;
		}
		if(level%4050==0){
			system("cls");
			color(0,12);
			lb(15);
			puts("ToLive v1.0.2");
			wline();
			color(0,14);
			cout<<user<<"\n金币："<<money<<"\n生命："<<healthy<<"\n";
			wline();
			color(0,11);
			cout<<"第"<<level<<"天\n";
			puts("你的背包：");
			have=0;
			for(long long i=0;i<5;i++)if(matter[i]){
				cout<<aname[i]<<"  x"<<matter[i]<<endl;
				have=1;
			}
			for(long long i=5;i<30;i++)if(matter[i]){
				cout<<aname[i%5]<<bname[i/5-1]<<'x'<<matter[i]<<endl;
				have=1;
			}
			for(long long i=30;i<36;i++)if(matter[i]){
				cout<<cname[i-30]<<'x'<<matter[i]<<endl;
				have=1;
			}
			if(!have)puts("空");
			wline();
			say("YHX","真厉害,\n");
			say("YHX","你经历了81次洗劫而幸存.\n");
			say("YHX","你一定非常强大.\n");
			say("YHX","是时候接受考验了.\n");
			say("你","什么考验?\n");
			say("YHX","打败我,你就可以离开,\n");
			say("YHX","不然就沉睡在这里吧!\n");
			say("你","什么?你不是向导吗?\n");
			say("YHX","受死吧!\n");
			say("你","啊啊啊!\n");
			getch();
			for(int i=0;i<10;i++){
				system("color f0");
				Sleep(50);
				system("color 0f");
				Sleep(50);
			}
			system("cls");
			say("你","嗯?\n");
			say("你","我在哪里?\n");
			say("陌生人","你好!\n");
			say("你","你是谁?\n");
			say("陌生人","我叫YHX.\n");
			say("你","YHX?!?!\n");
			say("陌生人","别怕,我是好YHX.\n");
			say("陌生人","我打败了坏YHX,\n");
			say("陌生人","我从他手里抢走了你,\n");
			say("你","为什么你么要用\"抢\"...\n");
			say("陌生人","现在一切从新开始!\n");
			say("陌生人","迎接全新的生活吧!\n");
			say("你","啊哈哈!\n");
			getch();
			money=1000;
			healthy=100;
			memset(matter,0,sizeof(matter));
		}
		kout<<user<<endl<<level<<' '<<money<<' '<<healthy<<endl;
		for(long long i=0;i<40;i++)kout<<matter[i]<<' ';
		kout.close();
	}
	system("cls");
	say("YHX","真不幸,又一个生存者离开了我们.\n");
	getch();
	ofstream kout("data.sgr");
	kout<<"MCH\n0 1000 100\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
	kout.close();
	return 0;
}
