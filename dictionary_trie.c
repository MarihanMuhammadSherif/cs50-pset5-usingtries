/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"




unsigned int dicsize=0;

 node_trie* root;
 

 


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */ 
bool load(const char* dictionary)
{
    // TODO
    root=calloc(1,sizeof(node_trie));
    root->is_word=false;
    int i;
    for(i=0;i<27;++i)
    {
        root->next[i]=NULL;
    }
    
 
    
    FILE* dicpt=fopen(dictionary,"r");
    if(dicpt==NULL)
   { return false;
   }
    
    
    //the root of the trie
      node_trie* cursor=root;
      char word[LENGTH +1];
    
     while( fscanf(dicpt,"%s\n",word)!=EOF)  
    {
          ++dicsize;
        for(i=0;word[i]!='\0';++i)
        {
            
            if(isalpha(word[i])!=0 && cursor->next[word[i]-'a']==NULL )
            {
        //create new node
                 node_trie* new_node=malloc(sizeof(node_trie));
                 cursor->next[   word[i]-'a'  ]=new_node;
                 
                for(i=0;i<27;++i)
                {
                      new_node->next[i]=NULL;
                }    
                 cursor=new_node;
                
            }
            else if(word[i]=='\'' && cursor->next[26]==NULL)
            {
                 node_trie* new_node=malloc(sizeof(node_trie));
                 cursor->next[26]=new_node;
                 
                for(i=0;i<27;++i)
                {
                      new_node->next[i]=NULL;
                }    
                 cursor=new_node;
            }
            else
            {
                cursor=cursor->next[word[i]-'a'];
            }
            //////////////////////////////////
            if(i==strlen(word)-1)
            {
                cursor->is_word=true;
            }
            else
            {
                cursor->is_word=false;
            }
            
        }
    }
    
    
    
    
    
   
fclose(dicpt);
    return true;
}












/**
 * Returns true if word is in dictionary else false.
 */
bool check(char* word)
{
    
node_trie* cursor=root;
    
char* low_word=malloc(sizeof(char)*(strlen(word)+1));
int i=0;
while((low_word[i]=tolower(word[i]))!='\0')
    {
        if(i<strlen(word)-1)
        {
        if(isalpha(low_word[i]) !=0 )
             {
                 if(cursor->next[low_word[i]-'a']==NULL)
                 {
                     return false;
                 }
                 else
                 {
                     cursor=cursor->next[low_word[i]-'a'];
                 }
             }
             
             else if(low_word[i]=='\'' )
             {
                 if(cursor->next[26]==NULL)
                 {
                     return false;
                 }
                 else
                 {
                     cursor=cursor->next[26];
                 }
                 
             }
             
        }
        if(i==strlen(word)-1 && (cursor->is_word==true))
        {
            return true;
        }
             ++i;
             
    }
    
   


    return false;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return dicsize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
 
void unloader(node_trie* cursor)
 {
 int i;
 for(i=0;i<27;++i)
 {
     if(cursor->next[i]==NULL)
     {
         free(cursor->next[i]);
         ++i;
     }
     else
     {
         return unloader(cursor->next[i]);
     }
 }
     
 }
bool unload(void)
{
    // TODO
unloader(root);
    return true;
}

