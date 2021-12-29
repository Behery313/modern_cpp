//BMI Author: Yusuf behery
//Date: 28/12/2021
////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>
#include <ios>
#include <iomanip>
 int compute_bmi(int height, int weight)
 {
     return  ((weight*10000/float(height*height))+0.5);
 }
void skip_line(void)//used to flush input buffer
{
    std::cin.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
}
bool get_record(std::vector<std::string> &names,std::vector <int> &heights ,std::vector<int> &weights,std::vector <char> &sexes)
{
    std::string name;
    int const & max_height=300;
    int const & max_weight=300;
    int weight;
    int height;
    char sex;
    char ans;
    std::cout<<"new entry? "<<std::endl<<"'y' or 'n'?";
    while(1)
    {
        std::cin>>ans;
        skip_line();
        if (ans=='y'||ans=='Y')
     //   return true;
        {
            break;//do nothing
        }
        else if (ans=='n'||ans=='N')
        return false;
        else
        std::cout<<"invalid input"<<std::endl<<"new entry? "<<std::endl<<"'y' or 'n'?";
    }
    std::cout<<"Name: ";
    getline(std::cin,name);
    std::cout<<"height: ";
    std::cin>>height;
    skip_line();
    while (height<0||height>max_height)
    {
        std::cout<<"invalid height";
        return false;

    }
    std::cout<<"weight: ";
    std::cin>>weight;
    if (weight<0||weight>max_weight)
    {
        std::cout<<std::endl<<"invalid height"<<std::endl;
        return false;
    }
    std::cout<<"sex:";
    std::cin>>sex;
    skip_line();
    if (sex!='M'&& sex!='m'&& sex!='F'&& sex!='f')
    {
        std::cout<<std::endl<<"invalid input";
        return false;
    }
    names.push_back(name);
    weights.push_back(weight);
    heights.push_back(height);
    sexes.push_back(sex);
   // std::cout<<"successful entry"<<std::endl;
    std::cout<<std::endl<<"name:"<<name<<std::endl<<"sex:"<<sex<<std::endl<<"weight:"<<weight<<std::endl<<"height:"<<height<<std::endl;
    return true;
    
}
void print_table(char sex ,
                std::vector<std::string> const &names,
                std::vector <int>const &heights ,
                std::vector<int>const &weights,
                std::vector <char> const &sexes,
                std::vector< int > const &bmis,
                int threshold )
{
    int max_name_size;
    float mean=0;
    float median;
    int counter=0;
    std::vector<int> sorted_bmis;
    //finding max length of names entered
        for(int i=0;i<names.size();i++)
        {
            if(names[i].size()>max_name_size)
            {
                max_name_size=names[i].size();
            }
        }
        ////
        ////////////////////////
        //printing defaults
       // std::cout<<std::left <<std::setw(max_name_size+5)<<"Name";
       // std::cout<<std::left <<std::setw(10)<<"sex";
       // std::cout<<std::left <<std::setw(12)<<"weight";
       // std::cout<<std::left <<std::setw(12)<<"height";
       // std::cout<<std::right<<std::setw(10)<<"BMI"<<std::endl;
        ////////////////////////
    for(int i=0;i<sexes.size();i++)
    {
        if (sex==sexes[i])
        {
            sorted_bmis.push_back(bmis[i]);
            counter++;
            mean=bmis[i]+mean;

            std::cout<<std::left<<std::setw(max_name_size+5)<<names[i]<<"\t";//5 extra spaces
            std::cout<<std::left <<std::setw(10)<<sexes[i];
            std::cout<<std::left <<std::setw(12)<<weights[i];
            std::cout<<std::left <<std::setw(12)<<heights[i];
            std::cout<<std::right<<std::setw(6)<<bmis[i];
            if(bmis[i]>=threshold)
            {
                std::cout<<"*";
            }
            std::cout<<std::endl;
        }
    }
    mean=mean/counter;
    std::sort(sorted_bmis.begin(),sorted_bmis.end());
    if(sorted_bmis.size()%2==0)//even 
    {
        median=(sorted_bmis[(sorted_bmis.size()-1)/2]+sorted_bmis[((sorted_bmis.size()-1)/2)+1])/2;
    }
    else//odd
    {
        median =sorted_bmis[(sorted_bmis.size()-1)/2];
    }
    std::cout<<"median BMI :"<<std::fixed<<std::setprecision(1)<<median<<std::endl;
    std::cout<<"mean BMI :"  <<std::fixed<<std::setprecision(1)<<mean<<std::endl<<std::endl;
}
int main ()
{
    std::vector<int> weights;
    std::vector<int> heights;
    std::vector<std::string> names;
    std::vector<int> bmis;
    std::vector<char> sexes;
    int threshold;
    std::cout<<"enter threshold"<<std::endl;
    std::cin>>threshold;
    skip_line();
    while(get_record(names,heights,weights,sexes))
    {
        bmis.push_back(compute_bmi(heights.back(),weights.back()));
        std::cout<<"BMI:"<<bmis.back()<<std::endl<<std::endl;
    }
    std::cout<<"Males"<<std::endl<<"-----"<<std::endl;
    print_table('m',names,heights,weights,sexes,bmis,threshold);
    std::cout<<"Females"<<std::endl<<"-------"<<std::endl;
    print_table('f',names,heights,weights,sexes,bmis,threshold);
}
