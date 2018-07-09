#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *InText ;
FILE *fp;
enum Symbols{S_FALSE,S_TRUE,S_PRINT,S_SBRA_C,
S_PAR_C,S_CBRA_O,S_CBRA_C,S_PAR_O,S_ASSIGN,
S_E, S_SEMI, S_ID, S_INTIGER,S_FLOAT,S_SBRA_O,
S_STRING,S_COLON, S_COMMA,S_QUT,
S_IF,S_ELSE,S_WHILE,S_FOR,S_ADD, S_SUB,
S_DIV, S_MUL, S_MOD, S_LT, S_LE,S_POW,
S_GT, S_GE, S_NE, S_NOT, S_AND, S_OR,S_NULL,S_COMMENT};
typedef struct TokenType{
    char Name[80];
    int ROW,COL,BLKNO,BLKORD;
    enum Symbols SYMBOL;
}TokenType;
struct TokenType MakeToken(enum Symbols symbol,int Col,int Row,int BN ,int BO,char word[80]){
    struct TokenType a;
    //a.Name=word[80];
    a.SYMBOL = symbol;
    strcpy(a.Name,word);
    a.COL=Col;
    a.ROW=Row;
    a.BLKNO=BN;
    a.BLKORD=BO;
    switch(symbol){
        case 0:
            fprintf(fp,"S_FALSE ");
            return a;
        case 1:
            fprintf(fp,"S_TRUE ");
            return a;
        case 2:
            fprintf(fp,"S_PRINT ");
            return a;
        case 3:
            fprintf(fp,"S_SBRA_C ");
            return a;
        case 4:
            fprintf(fp,"S_PAR_C ");
            return a;
        case 5:
            fprintf(fp,"S_CBRA_O ");
            return a;
        case 6:
            fprintf(fp,"S_CBRA_C ");
            return a;
        case 7:
            fprintf(fp,"S_PAR_O ");
            return a;
        case 8:
            fprintf(fp,"S_ASSIGN ");
            return a;
        case 9:
            fprintf(fp,"S_E ");
            return a;
        case 10:
            fprintf(fp,"S_SEMI ");
            return a;
        case 11:
            fprintf(fp,"S_ID ");
            return a;
        case 12:
            fprintf(fp,"S_INTIGER ");
            return a;
        case 13:
            fprintf(fp,"S_FLOAT ");
            return a;
        case 14:
            fprintf(fp,"S_SBRA_O ");
            return a;
        case 15:
            fprintf(fp,"S_STRING ");
            return a;
        case 16:
            fprintf(fp,"S_COLON ");
            return a;
        case 17:
            fprintf(fp,"S_COMMA ");
            return a;
        case 18:
            fprintf(fp,"S_QUT ");
            return a;
        case 19:
            fprintf(fp,"S_IF ");
            return a;
        case 20:
            fprintf(fp,"S_ELSE ");
            return a;
        case 21:
            fprintf(fp,"S_WHILE ");
            return a;
        case 22:
            fprintf(fp,"S_FOR ");
            return a;
        case 23:
            fprintf(fp,"S_ADD ");
            return a;
        case 24:
            fprintf(fp,"S_SUB ");
            return a;
        case 25:
            fprintf(fp,"S_DIV ");
            return a;
        case 26:
            fprintf(fp,"S_MUL ");
            return a;
        case 27:
            fprintf(fp,"S_MOD ");
            return a;
        case 28:
            fprintf(fp,"S_LT ");
            return a;
        case 29:
            fprintf(fp,"S_LE ");
            return a;
        case 30:
            fprintf(fp,"S_POW ");
            return a;
        case 31:
            fprintf(fp,"S_GT ");
            return a;
        case 32:
            fprintf(fp,"S_GE ");
            return a;
        case 33:
            fprintf(fp,"S_NE ");
            return a;
        case 34:
            fprintf(fp,"S_NOT ");
            return a;
        case 35:
            fprintf(fp,"S_AND ");
            return a;
        case 36:
            fprintf(fp,"S_OR ");
            return a;
        case 37:
            return a;
    }
}
enum Symbols IsKeyWord( char *word){
    if(strcmp(word,"if")==0)return S_IF;
    else if(strcmp(word,"False")==0)return S_FALSE;
    else if(strcmp(word,"True")==0)return S_TRUE;
    else if(strcmp(word,"and")==0)return S_AND;
    else if(strcmp(word,"or")==0)return S_OR;
    else if(strcmp(word,"print")==0)return S_PRINT;
    else if(strcmp(word,"else")==0)return S_ELSE;
    else if(strcmp(word,"while")==0)return S_WHILE;
    else if(strcmp(word,"for")==0)return S_FOR;
    else return S_ID;
};
void LexerError(char NextWord[],int row,int col,int blkno, int blkord){
    printf("Error");
    //printf("Error:\nWord=%s\nColumn=%d\nRow=%d\nBlkNumber=%d\nBlkOrder=%d\n----------------\n ",
           //NextWord,col-1,row,blkno,blkord);
}
struct TokenType lexer ( FILE *InText ){
    char NextChar , NextWord[80] ;
    int State , Length ;
    static char LastChar = '\0';
    static int RowNo =0, ColNo = 0 ,BlkNo = 0 , BlkOrd=0;
    State = 0 ;
    Length = 0 ;
    while (!feof(InText) ){        //BARAYE TAK TAK CHAR HA EJRA VA TASMIM GIRI KONAD...
        //printf("no+");
        //printf("true");
        if ( LastChar ){            //IF WE BEFORE READ A CHAR MORE
            NextChar = LastChar ;
            LastChar = '\0';
        }
        else{
            NextChar=fgetc(InText);
            NextWord[Length++] = NextChar;    //BARAYE HAR HARF JADID VA STATES OK E LENGTH HAM NEXTWORD
        }
        switch(State)
        {
            case 0:

                if(NextChar=='\n'){
                    RowNo++;
                    ColNo = 0;
                    Length=0;
                    break;
                }else ColNo++;

                if (NextChar==' '|| NextChar=='\t'){
                        Length = 0;
                        State=0;
                        break;
                }
                else if((NextChar<='z' && NextChar >= 'a') || ( NextChar<='Z' && NextChar >= 'A')) {State=1;break;} //0,letter,1
                else if (NextChar=='.'){State=3;break;}
                else if ( NextChar <='9' && NextChar >= '0' ){State = 2;break;}//0,digit,2
                else if (NextChar=='"'){State=4;break;}//0,",4
                else if (NextChar=='\''){State=13;break;}
                else if (NextChar=='<'){State=22;break;}
                else if (NextChar=='>'){State=24;break;}
                else if (NextChar=='='){State=26;break;}
                else if (NextChar=='<'){State=22;break;}
                else if (NextChar=='!'){State=27;break;}
                else if (NextChar=='+')return MakeToken(S_ADD,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else if (NextChar=='-')return MakeToken(S_SUB,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else if (NextChar=='*'){State=31;break;}
                else if (NextChar=='/'){State=33;break;}
                else if (NextChar=='#'){State=34;break;}
                else if (NextChar==';')return MakeToken(S_SEMI,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else if (NextChar==':')return MakeToken(S_COLON,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else if (NextChar==',')return MakeToken(S_COMMA,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else if (NextChar=='[')return MakeToken(S_SBRA_O,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else if (NextChar==']')return MakeToken(S_SBRA_C,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else if (NextChar=='(')return MakeToken(S_PAR_O,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else if (NextChar==')')return MakeToken(S_PAR_C,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else if (NextChar=='{'){BlkNo++;BlkOrd++;return MakeToken(S_CBRA_O,ColNo,RowNo,BlkNo,BlkOrd,NextWord);}
                else if (NextChar=='}'){BlkNo--;return MakeToken(S_CBRA_C,ColNo,RowNo,BlkNo,BlkOrd,NextWord);}
                else if (NextChar=='&')return MakeToken(S_AND,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else if (NextChar=='%')return MakeToken(S_MOD,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else {
                        LexerError(NextWord,RowNo,ColNo,BlkNo,BlkOrd);
                        return MakeToken(S_NULL,ColNo,RowNo,BlkNo,BlkOrd,NextWord);}
            case 1:
                ColNo++;
                if((NextChar<='z' && NextChar >= 'a') || ( NextChar<='Z' && NextChar >= 'A') ||
                   ( NextChar <='9' && NextChar >= '0' )||NextChar=='_')break; //(state = 1 mimanad...)
                else {
                        LastChar = NextChar ;
                        NextWord[Length-1] = '\0';
                        return MakeToken(IsKeyWord(NextWord),ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                        }
                break;
            case 2:
                ColNo++;
                if(NextChar=='.'){State=3;break;}
                else if(NextChar<='9' && NextChar>='0'){State=2;break;}
                else{
                    LastChar = NextChar ;
                    NextWord[Length-1] = '\0';
                    return MakeToken(S_INTIGER,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                }
                break;
            case 3:
                ColNo++;
                //printf("true");
                if(NextChar <= '9'&& NextChar >= '0'){State=3;break;}
                else{
                    LastChar = NextChar ;
                    NextWord[Length--] = '\0';
                    return MakeToken(S_FLOAT,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                    }
                    break;
            case 4:
                ColNo++;
                if (NextChar=='\\'){State=12;break;}
                else if(NextChar=='"'){State=6;break;}
                else {State=11;break;}
                break;
            case 5:
                ColNo++;
                if (NextChar=='"'){State=36;break;}
                else{
                    LastChar = NextChar ;
                    NextWord[Length-1] = '\0';
                    return MakeToken(S_STRING,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                }
                break;
            case 6:
                ColNo++;
                if(NextChar=='"'){State=7;break;}
                else{
                    LastChar = NextChar ;
                    NextWord[Length-1] = '\0';
                    return MakeToken(S_STRING,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                }
                break;
            case 7:
                ColNo++;
                if (NextChar=='"'){State=8;break;}
                else if(NextChar=='\\'){State=37;break;}
                else {State=7;break;}
                break;
            case 8:
                ColNo++;
                if (NextChar=='"'){State=9;break;}
                else if(NextChar=='\\'){State=37;break;}
                else State=7;
                break;
            case 9:
                ColNo++;
                if (NextChar=='"'){State=10;break;}
                else if(NextChar=='\\'){State=37;break;}
                else {State=7;break;}
                break;
            case 10:
                ColNo++;
                Length=0;
                State=0;
                return MakeToken(S_COMMENT,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                break;
            case 11:
                ColNo++;
                if (NextChar=='"')State=5;
                else if(NextChar=='\\')State=12;
                else State=11;
                break;
            case 12:
                ColNo++;
                State=11;
                break;
            case 13:
                ColNo++;
                if(NextChar=='\\')State=14;
                else if(NextChar=='\'')State=17;
                else State=15;
                break;
            case 14:
                ColNo++;
                State=15;
                break;
            case 15:
                ColNo++;
                if (NextChar=='\'')State=16;
                else if(NextChar=='\\')State=14;
                else State=15;
                break;
            case 16:
                ColNo++;
                if (NextChar=='\'')State=38;
                else{
                    LastChar = NextChar ;
                    NextWord[Length-1] = '\0';
                    return MakeToken(S_STRING,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                }
                break;
            case 17:
                ColNo++;
                if(NextChar=='\'')State=18;
                else{
                    LastChar = NextChar ;
                    NextWord[Length-1] = '\0';
                    return MakeToken(S_STRING,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                }
                break;
            case 18:
                ColNo++;
                if (NextChar=='\'')State=19;
                else if(NextChar=='\\')State=39;
                else State=18;
                break;
            case 19:
                ColNo++;
                if (NextChar=='\'')State=20;
                else if(NextChar=='\\')State=39;
                else State=18;
                break;
            case 20:
                ColNo++;
                if (NextChar=='\'')State=21;
                else if(NextChar=='\\')State=39;
                else State=18;
                break;
            case 21:
                ColNo++;
                Length=0;
                State=0;
                return MakeToken(S_COMMENT,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                break;
            case 22:
                ColNo++;
                if(NextChar=='=')State=23;
                else{
                        LastChar = NextChar ;
                        NextWord[Length-1] = '\0';
                        return MakeToken(S_LT,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                }
                break;
            case 23:
                return MakeToken(S_LE,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
            case 24:
                ColNo++;
                if(NextChar=='=')return MakeToken(S_GE,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else{
                        LastChar = NextChar ;
                        NextWord[Length-1] = '\0';
                        return MakeToken(S_GT,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                    }
                break;
            //case 25 nemikhad
            case 26:
                ColNo++;
                if(NextChar=='=')return MakeToken(S_E,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else {
                        LastChar = NextChar ;
                        NextWord[Length-1] = '\0';
                        return MakeToken(S_ASSIGN,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                }
                break;
            case 27: // !
                ColNo++;
                if (NextChar=='=')return MakeToken(S_NE,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else {LexerError(NextWord,RowNo,ColNo,BlkNo,BlkOrd);
                return MakeToken(S_NULL,ColNo,RowNo,BlkNo,BlkOrd,NextWord);;}
                break;
            //case 28:
                //return MakeToken(S_ADD,ColNo,RowNo,NextWord);
                //break;
            //case 30 nemikhad
            //case 29:
                //return MakeToken(S_SUB,ColNo,RowNo,NextWord);
                //break;
            case 31:
                ColNo++;
                if(NextChar=='*')return MakeToken(S_POW,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else{
                        LastChar = NextChar ;
                        NextWord[Length-1] = '\0';
                        return MakeToken(S_MUL,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                }
                break;
                //case 32 nemikhad
            case 33: // /
                ColNo++;
                if(NextChar=='/')return MakeToken(S_QUT,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                else{
                        LastChar = NextChar ;
                        NextWord[Length-1] = '\0';
                        return MakeToken(S_DIV,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
                }
                break;
            case 34:// # comment
                ColNo++;
                if(NextChar=='\n'){
                    Length=0;
                    State=0;
                }
                else State=34;
                break;
            //case 35 nemikhad
            case 36:
                ColNo++;
                if(NextChar=='"')State=5;
                else if(NextChar=='\\')State=12;
                else State=36;
                break;
            case 37:
                ColNo++;
                State=7;
                break;
            case 38:
                ColNo++;
                if(NextChar=='\'')State=16;
                else if(NextChar=='\\')State=14;
                else State=38;
                break;
            case 39:
                ColNo++;
                State=18;
                break;
        }//EOF SWITCH CASE
    }//EOF WHILE
    if(State==1)return MakeToken(S_ID,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
    if(State==2)return MakeToken(S_INTIGER,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
    if(State==3 && Length>2)return MakeToken(S_FLOAT,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
    if(State==34)return MakeToken(S_COMMENT,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
    LexerError(NextWord,RowNo,ColNo,BlkNo,BlkOrd);
    return MakeToken(S_NULL,ColNo,RowNo,BlkNo,BlkOrd,NextWord);
}//EOF lexer



void main ( void ){
InText = fopen("src.txt","r");
fp = fopen("Output_tokens.txt", "w");

//if ( argc < 2 ){
//printf("The file's name is forgotten! please cheek and retry! \n");
//}
//InText = fopen(argv[1],'r');
while(!feof(InText))
{
    struct TokenType Token;
    //printf("yes-");
    Token = lexer ( InText ) ;
    fprintf(fp,"\nWord=%s\nSymbolNumber=%d\nColumn=%d\nRow=%d\nBlkNumber=%d\nBlkOrder=%d\n----------------\n",
           Token.Name,Token.SYMBOL,Token.COL,Token.ROW,Token.BLKNO,Token.BLKORD);

}
fclose(fp);
fclose(InText);
}
