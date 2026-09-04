//declaring all header files
#include<stdio.h> //for printf and scanf functions
#include<string.h>//for strlen and strcmp functions
#include<ctype.h>//for tolower and isalnum functions
#include<math.h>//for log and other mathematical operations

//defining all constants
#define MAX_DOCS 50
#define MAX_LEN 5000
#define MAX_TOKENS 500
#define MAX_TOKEN_LEN 50
#define NUM_STOP_WORDS 8

//defining all 2D arrays globally;
char documents[MAX_DOCS][MAX_LEN];
char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
char stop_words[NUM_STOP_WORDS][MAX_TOKEN_LEN]={"the","is","a","an","and","in","of","to"};

//declaring all global variables;
int doc_count=0;
int token_count=0;

//all function prototypes
void help();
void normalize_case_all();
void tokenize_all();
void remove_stop_words_all();
void stem_all_tokens();
void compute_tf_idf_all(char word[]);
void display_stat();
double compute_tf(char word[],int doc_id);
double compute_idf(char word[]);

//main function
int main()
{
    for(int i=0;i<MAX_DOCS;i++)
        documents[i][0]='\0';
    char command[50];
    printf("Welcome to the Document Processing System!\n");
    help();
    while(1)
    {
        printf("Enter command:");
        fgets(command,50,stdin);//inside fgets,a string pointer , its size as integer and  input stream such as here is keyboard.
        command[strcspn(command,"\n")]='\0';//fgets stores as command\n\0 ,so to remove \n,this is used.otherwise in strcmp logical error will occur.

//takes all the input
        if(strcmp(command,"set")==0)
        {
            int docnum;
            printf("Enter the number of documents(1-50):");
            scanf("%d",&docnum);
            getchar();//removes the effect of enter pressing
//checks validity of docnum
            if(docnum<1 || docnum>50)
            {
                printf("Invalid number of documents.Must be from 1 to 50.\n");
                continue;
            }
            doc_count=docnum;//for use in other functions
            for(int i=0;i<docnum;i++)
            {
                printf("Enter document %d:",i+1);
                fgets(documents[i],MAX_LEN,stdin);
                documents[i][strcspn(documents[i],"\n")]='\0';
//checks validity of string length
                if(strlen(documents[i])>=MAX_LEN-1)//it should not exceed max length(null terminated)
                {
                    printf("Document too long\n");
                    documents[i][0]='\0';//initiates that one with a null character
                    doc_count=i;
                    break;//restarts taking the documents from the beginning
                }
            }
            printf("Documents set successfully. Please, enter 'preprocess' command now. It will not take other commands.\n");
        }
        else if(strcmp(command,"preprocess")==0)
        {
            normalize_case_all();
            tokenize_all();
            remove_stop_words_all();
            stem_all_tokens();
        }
        else if(strcmp(command,"tf")==0)
        {
            char word[50];
            printf("Enter the word to compute TF:");
            fgets(word,50,stdin);
            word[strcspn(word,"\n")]='\0';
            for(int i=0;i<doc_count;i++)
            {
                double tf= compute_tf(word,i);
                printf("Document %d: %.4f\n",i+1,tf);//doc number cannot start from 0
            }
        }
        else if(strcmp(command,"idf")==0)
        {
            char word[50];
            printf("Enter the word to compute IDF:");
            fgets(word,50,stdin);
            word[strcspn(word,"\n")]='\0';
            double idf= compute_idf(word);
            printf("IDF for '%s': %.4f\n",word,idf);
        }
        else if(strcmp(command,"tfidf")==0)
        {
            char word[50];
            printf("Enter the word to compute TF-IDF:");
            fgets(word,50,stdin);
            word[strcspn(word,"\n")]='\0';
            compute_tf_idf_all(word);
        }
        else if(strcmp(command,"stat")==0)
        {
            display_stat();
        }
        else if(strcmp(command,"exit")==0)
        {
            printf("Exiting program.\n");
            break;
        }
        else if(strcmp(command,"help")==0)
        {
            help();
        }
        else
        {
            printf("Unknown command.Type 'help' for list of commands.\n");
        }
    }
    return 0;
}

//help function
void help()
{
    printf("Commands:\n");
    printf(" set\t\t-Prompt for the number of documents and their text\n");
    printf(" preprocess\t-Apply normalization, tokenization, stop-words removal, and stemming orderly.\n");
    printf(" tf\t\t-Compute and display Term Frequency for a specified word across documents\n");
    printf(" idf\t\t-Compute and display Inverse Document Frequency for a specified word\n");
    printf(" tfidf\t\t-Compute and display TF-IDF scores for a specified word across documents\n");
    printf(" stat\t\t-Display TF,IDF,and TF-IDF for all tokens across all documents in a matrix format\n");
    printf(" help\t\t-Print the list of all available commands\n");
    printf(" exit\t\t-Exit the program\n");
}

//normalize case function
void normalize_case_all()
{
   if(doc_count==0)
   {
       printf("No documents set.Use 'set' command first\n");
   }
   else
   {
       printf("Normalized Documents:\n");
       for(int i=0;i<doc_count;i++)
       {
           for(int j=0;documents[i][j]!='\0';j++)//until null character is found ,the loop will go on
           {
               documents[i][j]=tolower(documents[i][j]);//tolower converts to lowercase
           }
           printf("Document %d: %s\n",i+1,documents[i]);//each string is printed.j defines each character of string,
       }
       printf("Documents normalized.\n");
   }
}

//tokenize all function
void tokenize_all()
{
    if(doc_count!=0)
    {
        token_count=0;
        printf("Tokens:\n");
        for(int i=0;i<MAX_TOKENS;i++)
            {
                tokens[i][0]='\0';//tokens array cleared
            }
        for(int i=0;i<doc_count;i++)
            {
                char array[MAX_LEN];
                strncpy(array,documents[i],MAX_LEN);//documents[i][MAX_LEN]=array[MAX_LEN]
                array[MAX_LEN-1]='\0';//the documents are copied to array to avoid manipulation and the end character is set null to indicate termination.
                int length=strlen(array);//measures the total length of the array
                int start=0;//start is introduced to show the start and end of each string.It is incremented gradually with respect to j.
                for(int j=0;j<=length;j++)//length is measured excluding the null terminator at the end
                {
                    if(!isalnum(array[j])||array[j]=='\0')//isalnum checks whether alphaneumeric or not ,if !isalnum is true then non-alphaneumeric and loop stops
                    {
                        if(j>start && token_count<MAX_TOKENS)//if j and start becomes equal then the loop will end.
                        {
                            int k;
                            for(k=0;k<j-start && k<MAX_TOKEN_LEN-1;k++)//j measures the characters in each token.
                            {
                                tokens[token_count][k]=array[start+k];//k and start are incremented alongside
                            }
                            tokens[token_count][k]='\0';//terminating characters are given
                            token_count++;
                        }
                        start=j+1;//start incremented at the end of each loop with respect to j
                    }
                }
            }
         for(int i=0;i<token_count;i++)
         {
             printf("%d. %s\n",i+1,tokens[i]);
         }
         printf("Tokenizaion  complete. Total tokens: %d\n",token_count);
    }
}

//remove stop word function
void remove_stop_words_all()
{
    if(doc_count!=0)
    {
        printf("Tokens after stop-word removal:\n");
        int position=0;
        for(int i=0;i<token_count;i++)
            {
                int stop=0;//flag of stop word
                for(int j=0;j<NUM_STOP_WORDS;j++)
                {
                    if(strcmp(tokens[i],stop_words[j])==0)
                    {
                        stop=1;
                        break;
                    }
                }
                if(!stop)
                {
                    if(position!=i)
                    {
                        strncpy(tokens[position],tokens[i],MAX_TOKEN_LEN);
                        tokens[position][MAX_TOKEN_LEN-1]='\0';
                    }
                    position++;
                }
            }
        token_count=position;
        for(int i=0;i<token_count;i++)
            {
                printf("%d. %s\n",i+1,tokens[i]);
            }
        printf("Stop-word removal complete. Tokens remaining: %d\n",token_count);
    }
}

//stem function
void stem_all_tokens()
{
    if(doc_count!=0)
    {
        int position=0;
        printf("Stemmed tokens:\n");
        for(int i=0;i<token_count;i++)
            {
                int length=strlen(tokens[i]);
                if(length>=3 && tokens[i][length-3]=='i'&& tokens[i][length-2]=='n'&& tokens[i][length-1]=='g')
                    {
                        tokens[i][length-3]='\0';
                    }
                else if(length>=2 && tokens[i][length-2]=='e'&& tokens [i][length-1]=='d')
                    {
                        tokens[i][length-2]='\0';
                    }
                else if(length>=1 &&tokens[i][length-1]=='s')
                    {
                        tokens[i][length-1]='\0';
                    }
                if(position!=i)
                    {
                        strncpy(tokens[position],tokens[i],MAX_TOKEN_LEN);
                        tokens[position][MAX_TOKEN_LEN-1]='\0';
                    }
                position++;
            }
        token_count=position;
        for(int i=0;i<token_count;i++)
            {
                printf("%d. %s\n",i+1,tokens[i]);
            }
        printf("Stemming complete. Total stemmed tokens: %d\n",token_count);
    }
}
//tf functions
double compute_tf(char word[],int doc_id)
{
       double p=0.0;
       if(doc_count==0)
        {
            printf("No documents set.Use 'set' command first\n");
            return p;
        }
       else
       {
           int word_count=0;
           int total_words=0;
           int start=0;
           char copy[MAX_LEN];
           strncpy(copy,documents[doc_id],MAX_LEN);
           copy[MAX_LEN-1]='\0';
           int len=strlen(copy);
           for(int i=0;i<=len;i++)//strlen doesnt count null terminator so = is applied
           {
               if(!isalnum(copy[i])||copy[i]=='\0')//checks the boundaries such as spaces and ends
               {
                   if(i>start)//start will only increment when a new word is found by prev logic of isalnum and null
                   {
                       char temp[MAX_TOKEN_LEN];//the word that is found first will get stored here
                       int j;
                       for(j=0;j<i-start && j<MAX_TOKEN_LEN;j++)//if it exceeds the max token length, then it will not run
                       {
                           temp[j]=copy[start+j];//each word is being copied here
                       }
                       temp[j]='\0';//end character should be null

                       //now we have copied the main document and we need to stem it
                       char stemmed[MAX_TOKEN_LEN];
                       strncpy(stemmed,temp,MAX_TOKEN_LEN);
                       stemmed[MAX_TOKEN_LEN-1]='\0';
                       int length=strlen(stemmed);
                       if(length>=3 && stemmed[length-3]=='i'&& stemmed[length-2]=='n'&& stemmed[length-1]=='g')
                        {
                            stemmed[length-3]='\0';
                        }
                       else if(length>=2 && stemmed[length-2]=='e'&& stemmed[length-1]=='d')
                        {
                            stemmed[length-2]='\0';
                        }
                       else if(length>=1 && stemmed[length-1]=='s')
                        {
                            stemmed[length-1]='\0';
                        }
                       if(strcmp(stemmed,word)==0)
                        word_count++;//found word count incrementation
                       int stop=0;
                       for(int k=0;k<NUM_STOP_WORDS;k++)
                       {
                           if(strcmp(temp,stop_words[k])==0)
                           {
                               stop=1;
                               break;
                           }
                       }
                       if(!stop)
                       {
                           total_words++;
                       }

                   }
                   start=i+1;//start will only increase when a word is found and copied
               }
           }
           if(total_words>0)
           {
               p=(double)word_count/total_words;//typecasting for floating values
               return p;
           }
       }

}
//idf functions
double compute_idf(char word[])
{
    double q=0.0;

    if(doc_count==0)
    {
        printf("No documents set.Use 'set' command first\n");
        return q;
    }
    else
    {
        int dox=0;
        for(int i=0;i<doc_count;i++)
        {
            int found=0;
            int start=0;
            char copy[MAX_LEN];
            strncpy(copy,documents[i],MAX_LEN);
            copy[MAX_LEN-1]='\0';
            int length=strlen(copy);
            for(int j=0;j<=length;j++)
            {
                if(!isalnum(copy[j])||copy[j]=='\0')
                {
                    if(j>start)
                    {
                        char temp[MAX_TOKEN_LEN];
                        int k;
                        for(k=0; k< j-start && k<MAX_TOKEN_LEN;k++)
                        {
                            temp[k]=copy[start+k];
                        }
                        temp[k]='\0';
                        char stemmed[MAX_TOKEN_LEN];
                        strncpy(stemmed,temp,MAX_TOKEN_LEN);
                        stemmed[MAX_TOKEN_LEN-1]='\0';
                        int length=strlen(stemmed);
                        if(length>=3 && stemmed[length-3]=='i'&& stemmed[length-2]=='n'&& stemmed[length-1]=='g')
                         {
                             stemmed[length-3]='\0';
                         }
                        else if(length>=2 && stemmed[length-2]=='e'&& stemmed[length-1]=='d')
                         {
                             stemmed[length-2]='\0';
                         }
                        else if(length>=1 && stemmed[length-1]=='s')
                         {
                             stemmed[length-1]='\0';
                         }
                        if(strcmp(stemmed,word)==0)
                        {
                            found=1;//found word in the document
                            break;
                        }
                    }
                    start=j+1;
                }
            }
            if(found)
             dox++;
          }
           q=log10((double)MAX_DOCS/(1+dox));
           return q;
    }
}
//tf-idf functions
void compute_tf_idf_all(char word[])
{
    if(doc_count==0)
    {
        printf("No documents set.Use 'set' command first\n");
    }
    else
    {
        double idf=compute_idf(word);
        printf("TF-IDF for '%s':\n",word);
        for(int i=0;i<doc_count;i++)
        {
            double tf=compute_tf(word,i);
            printf("Document %d: %.4f\n",i+1,tf*idf);
        }
    }
}
//stat functions
void display_stat()
{
    if(doc_count==0)
    {
        printf("No documents set.Use 'set' command first\n");
    }
    else
    {
        //bubble sort algorithm
        for(int i=0;i<token_count-1;i++)
        {
            for(int j=0;j<token_count-i-1;j++)
            {
                if(strcmp(tokens[j],tokens[j+1])>0)
                {
                    char temp[MAX_TOKEN_LEN];
                    strncpy(temp,tokens[j],MAX_TOKEN_LEN);
                    temp[MAX_TOKEN_LEN-1]='\0';
                    strncpy(tokens[j],tokens[j+1],MAX_TOKEN_LEN);
                    tokens[j][MAX_TOKEN_LEN-1]='\0';
                    strncpy(tokens[j+1],temp,MAX_TOKEN_LEN);
                    tokens[j+1][MAX_TOKEN_LEN-1]='\0';
                }
            }
        }
        //order
        int count=1;
        for(int i=0;i<token_count;i++)
        {
            if(strcmp(tokens[count-1],tokens[i])!=0)
            {
                if(count!=i)
                {
                    strncpy(tokens[count],tokens[i],MAX_TOKEN_LEN);
                    tokens[count][MAX_TOKEN_LEN-1]='\0';
                }
                count++;
            }
        }
        token_count=count;
        //Display TF
        printf("============== TF ================\n");
        printf("                    ");
        for(int i=0;i<doc_count;i++)
        {
            printf(" doc %d        ",i+1);
        }
        printf("\n");
        for(int i=0;i<token_count;i++)
        {
            printf("%-20s",tokens[i]);
            for(int j=0;j<doc_count;j++)
            {
                double tf=compute_tf(tokens[i],j);
                printf("%.4f        ",tf);
            }
            printf("\n");
        }
        //display idf
        printf("============== IDF ================\n");
        printf("                        IDF\n ");
        for(int i=0;i<token_count;i++)
        {
            printf("%-20s",tokens[i]);
            double idf=compute_idf(tokens[i]);
            printf("%.4f         \n ",idf);
        }
        //display tf-tdf
        printf("============== TF-IDF ================\n");
        printf("                    ");
        for(int i=0;i<doc_count;i++)
        {
            printf(" doc %d        ",i+1);
        }
        printf("\n");
        for(int i=0;i<token_count;i++)
        {
            printf("%-20s",tokens[i]);
            for(int j=0;j<doc_count;j++)
            {
                double tf=compute_tf(tokens[i],j);
                double idf=compute_idf(tokens[i]);
                printf("%.4f        ",tf*idf);
            }
            printf("\n");
        }
    }
}
