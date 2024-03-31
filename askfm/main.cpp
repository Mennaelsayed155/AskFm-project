#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;
fstream regdatabase;
fstream questions;
fstream answers;
void fast()
{
    std::ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
}
struct userr
{
    string name;
    long long password,id;
}user;

struct q_ans{
    string q;
    long long idto,idfrom,qnum;
}qq_ans;

vector<userr>regdata;
vector<q_ans>ques,ans;
class services{
public:
    void viewusers()
    {

        for(auto k:regdata)
        {
            cout<<k.name<<"\n";
        }
    }
    void upload_regdata() {
        regdatabase.close();
        regdatabase.open("regdatabase.txt", ios::in);
        userr data;
        while(regdatabase>>data.name>>data.password>>data.id)
        {
            regdata.push_back(data);
        }
    }
    void upload_questions() {
        questions.close();
        questions.open("questions.txt", ios::in);
        q_ans q;
        while (questions >> q.idfrom >> q.idto >> q.qnum) {
            questions.ignore();
            getline(questions, q.q);
            ques.push_back(q);
        }
    }
    void upload_ans() {
        answers.close();
        answers.open("answers.txt", ios::in);
        q_ans an;
        while(answers>>an.idfrom>>an.idto>>an.qnum)
        {
            answers.ignore();
            getline(answers,an.q);
            ans.push_back(an);
        }


    }
    void dawonload_regdata() {
        regdatabase.close();
        regdatabase.open("regdatabase.txt", ios::out|ios::trunc);
        userr data;
        for(long long k=0;k<regdata.size();k++)
        {
            regdatabase<<regdata[k].name<<" "<<regdata[k].password<<" "<<regdata[k].id<<"\n";
        }

    }
    void dawonload_q()
    {
        questions.close();
        questions.open("questions.txt", ios::out|ios::trunc);
        for(long long k=0;k<ques.size();k++)
        {
            questions<<ques[k].idfrom<<"\n"<<ques[k].idto<<"\n"<<ques[k].qnum<<"\n"<<ques[k].q<<"\n";
        }
    }
    void dawonload_ans()
    {
        answers.close();
        answers.open("answers.txt", ios::out|ios::trunc);
        for(long long k=0;k<ans.size();k++)
        {
            answers<<ans[k].idfrom<<"\n"<<ans[k].idto<<"\n"<<ans[k].qnum<<"\n"<<ans[k].q<<"\n";
        }
    }
    bool checkpass(long long pass)
    {

        for(auto k:regdata)
        {

            if(k.password==pass)
            {
                return true;
            }
        }
        return false;
    }
    bool find_q_ans(vector<q_ans>v,long long qnumm)
    {
        for(auto k:v)
        {
            if(k.qnum==qnumm)
            {
                return true;
            }
        }
        return false;
    }

    bool access_dq_ans(vector<q_ans>v,long long idd,long long qnumm)
    {
        //cout<<v.size()<<" ";
        // cout<<qnumm<<" "<<idd<<"\n";
        for(auto k:v)
        {
            //   cout<<k.qnum<<" "<<k.idto<<"\n";
            if(k.qnum==qnumm&&k.idto==idd)
            {
                return true;
            }
        }
        return false;
    }
    bool access_eq_ans(vector<q_ans>v,long long idd,long long qnumm)
    {

        for(auto k:v)
        {
            if(k.qnum==qnumm&&k.idfrom==idd)
            {
                return true;
            }
        }
        return false;
    }
    bool checkid(long long idd)
    {
        for(auto k:regdata)
        {

            if(k.id==idd)
            {
                return true;
            }
        }

        return false;
    }

}op;

class userop{
public:
    void signup()
    {
        op.upload_regdata();
        cout<<"enter ur first name\n";
        cin>>user.name;
        cout<<"enter ur password\n";
        cin>>user.password;
        if(!op.checkpass(user.password))
        {
            if(regdata.size()==0){
                user.id=1;
            }
            else{
                user.id=regdata.back().id+1;
            }
            regdatabase.close();
            regdatabase.open("regdatabase.txt",ios::out|ios::app);
            regdatabase<<user.name<<" "<<user.password<<" "<<user.id<<"\n";

            cout<< "Congratulations, now U have activated account, Ur id is "<<user.id;
        }
        else
        {
            cout<<"This password already exists, please try again";
        }

    }

    void login()
    {
        op.upload_regdata();
        cout<<"enter ur name\n";
        cin>>user.name;
        cout<<"enter ur password\n";
        cin>>user.password;
        cout<<"enter ur id\n";
        cin>>user.id;
        if(op.checkpass(user.password)&&op.checkid(user.id))
        {
            cout<<"Welcome back";
        }
        else
        {
            cout<<"login info is not correct, try again";
        }
        // op.dawonload_regdata();
    }

    void deleteaccount() {
        cout << "enter ur name\n";
        cin >> user.name;
        cout << "enter ur password\n";
        cin >> user.password;
        cout << "enter ur id\n";
        cin >> user.id;
        op.upload_regdata();
        if (!op.checkpass( user.password) || !op.checkid(user.id)) {
            cout << "this account is not found , plz try again";
        } else {
            for (long long k = 0; k < regdata.size(); k++) {
                if (regdata[k].id == user.id && regdata[k].password == user.password) {
                    regdata.erase(regdata.begin() + k);
                }
            }
            services s;
            s.dawonload_regdata();
            cout << "ur account is deleted ";
        }
    }


};
class ans_q{
public:
    virtual void  add()=0;
    virtual void  delet_fromme()=0;
    virtual void  delet_my_q_s()=0;
    virtual void  show_tou()=0;
    virtual void  show_fromu()=0;
    virtual void  update()=0;
};

class question:public ans_q{

protected:
    void add()
    {
        cout<<"enter ur id ";
        cin>>qq_ans.idfrom;
        cout<<"enter user's id who you want to ask: ";
        cin>>qq_ans.idto;
        cin.ignore();
        cout<<"enter ur question";
        getline(cin,qq_ans.q);
        op.upload_regdata();
        if(!op.checkid(qq_ans.idfrom))
        {
            cout<<"this account is not activated,plz check ur registration data";
        }
        else  if(!op.checkid(qq_ans.idto))
        {
            cout<<"this account is not activated ";
        }
        else
        {
            if(ques.size()!=0)
            {
                services s;
                s.upload_questions();
                for(long long i=0;i<ques.size();i++)
                {
                    if(ques[i].q==qq_ans.q)
                    {
                        cout<<"This question has already been asked before.check the answers first.";
                        break;
                    }
                }
            }


            questions.close();
            questions.open("questions.txt", ios::out|ios::app);
            if(ques.size()==0) {qq_ans.qnum=1;}
            else qq_ans.qnum=ques.back().qnum+1;
            questions<<qq_ans.idfrom<<"\n"<<qq_ans.idto<<"\n"<<qq_ans.qnum<<"\n";
            questions<<qq_ans.q<<"\n";
            cout<<"ur question has been successfully added. Wait for the response\n";
            cout<<"question num is "<<qq_ans.qnum<<"\n";
            ques.push_back(qq_ans);
        }


    }
    void delet_my_q_s()
    {

    }
    void delet_fromme()  //delete from me
    {
        cout<<"enter ur id";
        cin>>qq_ans.idto;
        cout<<"enter question number ";
        cin>>qq_ans.qnum;
        op.upload_questions();
        if(!op.find_q_ans(ques,qq_ans.qnum))
        {
            cout<<"This question does not exist.maybe you deleted it previously";
        }
        else if(!op.access_dq_ans(ques,qq_ans.idto,qq_ans.qnum))
        {
            cout<<"u haven't have access to delete this question";
        }
        else
        {

            for(long long i=0;i<ques.size();i++)
            {
                if(ques[i].qnum==qq_ans.qnum)
                {
                    ques.erase(ques.begin()+i);
                }
            }
            questions.clear();
            services s;
            s.dawonload_q();
            cout<<"This question was successfully deleted";

        }

    }

    void show_tou()
    {
        cout<<"enter ur id";
        cin>>qq_ans.idto;
        bool c;
        ques.clear();
        op.upload_questions();
        //cout<<ques.size()<<" ";
        for(long long i=0;i<ques.size();i++)
        {
            if(ques[i].idto==qq_ans.idto)
            {
                c=1;
                cout<<ques[i].q<<"\n";
            }
        }
        if(!c)
        {
            cout<<"u haven't question yet ";
        }
    }
    void show_fromu()
    {
        cout<<"enter ur id";
        cin>>qq_ans.idfrom;
        ques.clear();
        op.upload_questions();
        bool b;
        for(long long i=0;i<ques.size();i++)
        {
            if(ques[i].idfrom==qq_ans.idfrom)
            {
                cout<<ques[i].q<<"\n";
                b=1;
            }
        }
        if(!b)
        {
            cout<<"u haven't asked anyone before.";
        }
    }
    void update()
    {
        cout<<"enter ur id";
        cin>>qq_ans.idfrom;
        cout<<"enter question number ";
        cin>>qq_ans.qnum;
        cin.ignore();
        cout<<"enter ur modified question ";
        getline(cin,qq_ans.q);
        ques.clear();
        op.upload_questions();
        if(!op.find_q_ans(ques,qq_ans.qnum))
        {
            cout<<"This question does not found";
        }
        else if(!op.access_eq_ans(ques,qq_ans.idfrom,qq_ans.qnum))
        {
            cout<<"u haven't had access to edit this question";
        }
        else
        {

            for(long long i=0;i<ques.size();i++)
            {
                if(ques[i].qnum==qq_ans.qnum)
                {
                    ques[i].q=qq_ans.q;
                }
            }
            services s;
            questions.clear();
            s.dawonload_q();
            cout<<"This question was successfully edited";
        }

    }
};
class answerss:public ans_q{
public:
    void add()
    {
        cout<<"enter ur id ";
        cin>>qq_ans.idfrom;
        cout<<"enter questioner's id : ";
        cin>>qq_ans.idto;
        cout<<"enter question's number: ";
        cin>>qq_ans.qnum;
        cin.ignore();
        cout<<"enter ur answer";
        getline(cin,qq_ans.q);
        op.upload_regdata();
        op.upload_questions();
        if(!op.checkid(qq_ans.idfrom))
        {
            cout<<"ur account is not activated,plz check ur registration data";
        }
        else  if(!op.checkid(qq_ans.idto))
        {
            cout<<"u can't add answer for this account because it is not activated ";
        }

        else if(!op.find_q_ans(ques,qq_ans.qnum))
        {
            cout<<"You can't answer to this question; it may be deleted or modified. Try again.";
        }
        else
        {
            answers.close();
            answers.open("answers.txt", ios::out|ios::app);
            answers<<qq_ans.idfrom<<"\n"<<qq_ans.idto<<"\n"<<qq_ans.qnum<<"\n";
            answers<<qq_ans.q<<"\n";
            cout<<"thanks,ur response is recorded \n";
            ans.push_back(qq_ans);
        }
    }
    void delet_fromme()//from me
    {
        cout<<"enter ur id ";
        cin>>qq_ans.idto;
        cout<<"enter question's number: ";
        cin>>qq_ans.qnum;
        cin.ignore();
        ans.clear();
        op.upload_ans();
        if(!op.access_dq_ans(ans,qq_ans.idto,qq_ans.qnum))
        {
            cout<<"This account has no reply on this question , maybe it deleted";
        }
        else
        {
            for(long long i=0;i<ans.size();i++)
            {
                if(ans[i].qnum==qq_ans.qnum)
                {
                    ans.erase(ans.begin()+i);
                }
            }
            services s;
            answers.clear();
            s.dawonload_ans();
            cout<<"ur answer was successfully deleted";
        }

    }
    void delet_my_q_s()//from me
    {
        cout<<"enter ur id ";
        cin>>qq_ans.idfrom;
        cout<<"enter question's number: ";
        cin>>qq_ans.qnum;
        cin.ignore();
        ans.clear();
        op.upload_ans();
        if(!op.access_eq_ans(ans,qq_ans.idfrom,qq_ans.qnum))
        {
            cout<<"You didn't answer on this question";
        }
        else
        {
            for(long long i=0;i<ans.size();i++)
            {
                if(ans[i].qnum==qq_ans.qnum)
                {
                    ans.erase(ans.begin()+i);
                }
            }
            services s;
            answers.clear();
            s.dawonload_ans();
            cout<<"ur answer was successfully deleted";
        }

    }

    void show_tou()
    {
        cout<<"enter ur id";
        cin>>qq_ans.idto;
        ans.clear();
        ans.clear();
        op.upload_ans();
        bool c;
        for(long long i=0;i<ans.size();i++)
        {
            if(ans[i].idto==qq_ans.idto)
            {
                c=1;
                cout<<ans[i].q<<"\n";
            }
        }
        if(!c)
        {
            cout<<"u haven't answers";
        }
    }
    void show_fromu()
    {
        cout<<"enter ur id";
        cin>>qq_ans.idfrom;
        ans.clear();
        op.upload_ans();
        bool b;
        for(long long i=0;i<ans.size();i++)
        {
            if(ans[i].idfrom==qq_ans.idfrom)
            {
                cout<<ans[i].q<<"\n";
                b=1;
            }
        }
        if(!b)
        {
            cout<<"u didn't add any answer yet";
        }
    }
    void update()
    {
        cout<<"enter ur id";
        cin>>qq_ans.idfrom;
        cout<<"enter question number ";
        cin>>qq_ans.qnum;
        cin.ignore();
        cout<<"enter ur modified answer ";
        getline(cin,qq_ans.q);
        ans.clear();
        op.upload_ans();
        if(!op.find_q_ans(ans,qq_ans.qnum))
        {
            cout<<"This answer does not found";
        }
        else if(!op.access_eq_ans(ans,qq_ans.idfrom,qq_ans.qnum))
        {
            cout<<"u haven't had access to edit this answer";
        }
        else
        {
            for(long long i=0;i<ans.size();i++)
            {
                if(ans[i].qnum==qq_ans.qnum)
                {
                    ans[i].q=qq_ans.q;
                }
            }
            services s;
            answers.clear();
            s.dawonload_ans();
            cout<<"ur reply is successfully edited";
        }
    }



};

void option(long long choice)

{

    /*services s;
            s.upload_regdata();//to vector
           s.upload_questions();
           s.upload_ans();
       regdatabase.clear();
       questions.clear();
       answers.clear();
       cout<<regdata.size()<<" "<<ques.size()<<" "<<ans.size()<<"\n";

        s.dawonload_regdata(); //to files
        s.dawonload_q();
        s.dawonload_ans();*/
    ans_q *ptr,*ptr2;
    question opp;
    answerss ob;
    ptr2= &ob;
    ptr = &opp;

    if(choice==0)
    {
        userop op;
        op.signup();
    }
    else if(choice==1)
    {
        userop op;op.login();
    }
    else if(choice==2) {

        ptr->add();
    }
    else if(choice==3) {

        ptr->show_tou();
    }
    else if(choice==4)
    {
        ptr->show_fromu();
    }
    else if(choice==5)
    {
        ptr2->add();
    }
    else if(choice==6) {

        ptr2->show_tou();
    }
    else if(choice==7) {

        ptr2->show_fromu();
    }
    else if(choice==8)
    {
        regdata.clear();
        op.upload_regdata();
        services s;
        s.viewusers();
    }
    else if(choice==9)
    {
        userop op;
        op.deleteaccount();
    }
    else if(choice==10)
    {
        ptr->delet_fromme();
    }
    else if(choice==11)
    {
        ptr2->update();
    }
    else if(choice==12)
    {
        ptr->update();
    }
    else if(choice==13)
    {
        ptr2->delet_my_q_s();
    }
    else if(choice==14)
    {
        ptr2->delet_fromme();
    }




}
int main() {
    // fast();
    cout << "Welcome, plz enter ur choice  \n"
            "0 : sign up "
            "\n1 : log in "
            "\n2 : asking a question"
            "\n3 : display questions you recieved"
            "\n4 : display questions you asked"
            "\n5 : reply to question"
            "\n6 : display the replies on ur account"
            "\n7 : Display your responses for other accounts."
            "\n8 : View all users in the system"
            "\n9 : delete your account "
            "\n10: delete a question"
            "\n11: update your reply"
            "\n12: update your question"
            "\n13: delete ur reply from another account"
            "\n14: delete replies from ur account"
            "\n15: log out\n";
    long long choice;
    while(1)
    {
        try {
            cin >> choice;
            if(choice==15)
            {
                cout<<"u logged out ";
                return 0;
            }
            if (!(choice >= 0 && choice <= 14)) {
                throw "your choice is not available, try again";
            }
            else {
                option(choice); }
        }
        catch (const char *m) {
            cout << m;
        }

    }


    return 0;
}



