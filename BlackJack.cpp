#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
using namespace std;
int  givecards();   //To originate cards.
int  showcards(int); //To show the cards on screen
int  player_turn();//To let users make decisions.
int  computer_turn(int);// To let computer make decision.
double  numchange(int); // To change sepcial cards.e.g. JQK
char input();           // To judge inputs.
bool  judging(char);
static double playernum = 0,computernum = 0;// The sum of all cards
static int playercard[12] ={0};     // To save cards
static int computercard[12]={0};    // To save cards



int main()
{

    int  num,color,card,playercards,i,j;
    bool flag  = true;
    char choice;
    srand(time(NULL));
    while(flag == true)
    {
        cout << "You get two cards,they are:" << endl;
        for (i = 0;i < 2; i++)
        {
            playercard[i] = givecards();
            num = showcards (playercard[i]);
            num = numchange(num);
            playernum += num;
        }
        playercards = player_turn();
        choice = computer_turn(playercards);
        flag = judging(choice);
        playernum = 0, computernum = 0;
        for (i = 0;i < 12; i++ )
        playercard[i] = computercard[i] = 0;
    }
}


int givecards()
{
    static int i=0,CARD;
    int j;
    static int card[52]={0};
    bool flag =true;
    while (flag)
    {
        flag = false;
        card[i] = CARD = rand() % 52;
        for(j = 0; j <= i ; j++)                // Ensure no same cards
        {
            if (card[i] == card[j] && i != j)
            flag = true;

        }
    }
    i ++ ;
    return CARD + 1;
}


int showcards(int card)
{
    int color,num;
    color = card % 4;
    num = card % 13 + 1;
    switch(color)                       // Make outputs by different cases
    {
        case 0 : cout << "hearts" <<" "; break;
        case 1 : cout << "spade" << " "; break;
        case 2 : cout << "diamand"<< " ";break;
        case 3 : cout << "club" << " "   ;break;
    }
    switch (num)
    {
        case 1  : cout << "A"; break;
        case 11 : cout << "J"; break;
        case 12 : cout << "Q"; break;
        case 13 : cout << "K"; break;
        default : cout << num; break;
    }
    cout << endl;
    return num;
}


int player_turn()
{
    char dec;
    int card,num,i,j;
    char choice;
    cout << "Need cards?(Y/N)" << endl;
    dec = input();
    while(dec == 'Y' || dec == 'y')
    {
        cout << "You get one more card.The cards are:" << endl;
        for (i = 1; i < 12;i++)
        {
            if (playercard[i] == 0)
            {playercard[i] = givecards ();break;}
        }
        for(j = 0; j <= i; j++)
        {num = showcards(playercard[j]);}
        num = numchange(num);
        playernum += num;
        if (playernum > 21) break;
        cout << "Need cards?(Y/N)" << endl;
        dec = input();
    }
    if (playernum > 21 )
    {cout << "you lose." << endl;}
    else return i;
}


int computer_turn(int playercards)
{
    int  color,num,card,i,j;
    char choice;
    if (playernum <= 21)
    {
        cout << "The computer gets two cards,they are:" << endl;
        for (i = 0;i < 2; i++)
        {
            computercard[i] = givecards ();
            num = showcards (computercard[i]);
            num = numchange(num);
            computernum += num;
        }
        while(computernum <= playernum && computernum < 21)
        {
            cout << "The computer gets one more card.The cards are:" << endl;
            for (i = 2; i < 12; i++)
            {
                if (computercard[i] == 0)
                {computercard[i] = givecards ();break;}
            }
            for(j = 0; j <= i; j++)
            {num = showcards(computercard[j]);}
            num = numchange(num);
            computernum += num;
            cout << endl;
        }
        if (computernum > playernum && computernum <= 21)       // The judge of who wins.
            cout << "You lose." << endl;
        if (computernum > 21)
            cout << "You win!" << endl;
        if (computernum == 21 && playernum == 21)
        {
            if(i < playercards)
                cout << "You win!" << endl;
            if (i > playercards)
                cout << "You lose." << endl;
            if (i == playercards)
                cout << "Dual" <<endl;
        }
    }
    cout << "Do you want to continue playing?(Y/N)" << endl;
    choice = input();
    return choice;
}


double numchange(int num)
{
    int changednum;
    switch(num)
    {
        case 11 :
        case 12 :
        case 13 : changednum = 0.5;break;
        default : changednum = num;break;
    }
    return changednum;
}


bool judging(char choice)
{
    if (choice == 'Y' || choice == 'y')
    return true;
    if (choice == 'N')
    return false;
}

char input()
{
    char *flag = new char(100);
    while(true)
    {
        cin >> flag;
        if(strlen(flag) > 1)
        {   cout << "Your input is wrong!" << endl;
            continue;}
        if(flag[0] == 'Y' || flag[0] == 'y' || flag[0] == 'N' || flag[0] == 'n') break;
        try
        {
            throw(flag);
        }
        catch(char*){cout <<"Your input is wrong!" << endl;}
    }
    return flag[0];
}
