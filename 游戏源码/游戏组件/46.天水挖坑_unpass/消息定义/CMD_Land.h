#ifndef CMD_LAND_HEAD_FILE
#define CMD_LAND_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//公共宏定义

#define KIND_ID						1171							//游戏 I D
#define GAME_PLAYER					3									//游戏人数
#define GAME_NAME					TEXT("天水挖坑")						//游戏名字
#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_GOLD)	//游戏类型

//Add by 20071129
#define LEFT_CARD_NUM	4 //留牌
#define ONE_USER_GET_CARD_NUM	14//每人得牌
#define ZHUANG_CARD_NUM   (LEFT_CARD_NUM+ONE_USER_GET_CARD_NUM)       //庄家牌数
#define ALL_CARD_NUM    (ONE_USER_GET_CARD_NUM*GAME_PLAYER + LEFT_CARD_NUM)//总牌数 46 52

//0x24,0x25,0x26,0x27,0x28
#define RED_4   0x24//红心4
#define MAX_RED_LENGTH  4//红8 

#define CARD_VALUE_THREE 16
#define CARD_VALUE_K	0x0D
//End add

//游戏状态
#define GS_WK_FREE					GS_FREE								//等待开始
#define GS_WK_SCORE					GS_PLAYING							//叫分状态
#define GS_WK_PLAYING				GS_PLAYING+1						//游戏进行

//////////////////////////////////////////////////////////////////////////
//服务器命令结构

#define SUB_S_SEND_CARD				100									//发牌命令
#define SUB_S_LAND_SCORE			101									//叫分命令
#define SUB_S_GAME_START			102									//游戏开始
#define SUB_S_OUT_CARD				103									//用户出牌
#define SUB_S_PASS_CARD				104									//放弃出牌
#define SUB_S_GAME_END				105									//游戏结束

//游戏状态
struct CMD_S_StatusFree
{
	LONG							lBaseScore;							//基础积分
};

//游戏状态
struct CMD_S_StatusScore
{
	BYTE							bLandScore;							//地主分数
	LONG							lBaseScore;							//基础积分
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bScoreInfo[GAME_PLAYER/*3*/];						//叫分信息
	BYTE							bCardData[ONE_USER_GET_CARD_NUM/*17*/];						//手上扑克
};

//游戏状态
struct CMD_S_StatusPlay
{
	WORD							wLandUser;							//坑主玩家
	WORD							wBombTime;							//炸弹倍数
	LONG							lBaseScore;							//基础积分
	BYTE							bLandScore;							//地主分数
	WORD							wLastOutUser;						//出牌的人
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bBackCard[LEFT_CARD_NUM/*3*/];						//底牌扑克
	BYTE							bCardData[ZHUANG_CARD_NUM /*20*/];						//手上扑克
	BYTE							bCardCount[GAME_PLAYER/*3*/];						//扑克数目
	BYTE							bTurnCardCount;						//基础出牌
	BYTE							bTurnCardData[ZHUANG_CARD_NUM/*20*/];					//出牌列表
};

//发送扑克
struct CMD_S_SendCard
{
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bCardData[ONE_USER_GET_CARD_NUM/*17*/];						//扑克列表
};

//用户叫分
struct CMD_S_LandScore
{
	WORD							bLandUser;							//叫分玩家
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bLandScore;							//上次叫分
	BYTE							bCurrentScore;						//当前叫分
};

//游戏开始
struct CMD_S_GameStart
{
	WORD				 			wLandUser;							//地主玩家
	BYTE							bLandScore;							//地主分数
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bBackCard[LEFT_CARD_NUM/*3*/];						//底牌扑克
};

//用户出牌
struct CMD_S_OutCard
{
	BYTE							bCardCount;							//出牌数目
	WORD				 			wCurrentUser;						//当前玩家
	WORD							wOutCardUser;						//出牌玩家
	BYTE							bCardData[ZHUANG_CARD_NUM/*20*/];						//扑克列表
};

//放弃出牌
struct CMD_S_PassCard
{
	BYTE							bNewTurn;							//一轮开始
	WORD				 			wPassUser;							//放弃玩家
	WORD				 			wCurrentUser;						//当前玩家
};

//游戏结束
struct CMD_S_GameEnd
{
	LONG							lGameTax;							//游戏税收
	LONG							lGameScore[GAME_PLAYER/*3*/];						//游戏积分
	BYTE							bCardCount[GAME_PLAYER/*3*/];						//扑克数目
	BYTE							bCardData[ALL_CARD_NUM];						//扑克列表 
};

//////////////////////////////////////////////////////////////////////////
//客户端命令结构

#define SUB_C_LAND_SCORE			1									//用户叫分
#define SUB_C_OUT_CART				2									//用户出牌
#define SUB_C_PASS_CARD				3									//放弃出牌

//用户叫分
struct CMD_C_LandScore
{
	BYTE							bLandScore;							//地主分数
};

//出牌数据包
struct CMD_C_OutCard
{
	BYTE							bCardCount;							//出牌数目
	BYTE							bCardData[ZHUANG_CARD_NUM/*20*/];						//扑克列表
};

//////////////////////////////////////////////////////////////////////////

#endif