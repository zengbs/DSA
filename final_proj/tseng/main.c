#include "api.h"
#define MAX 302
#define CHAIN_LENGTH 100

typedef struct
{
    int  token_num;                                   // 多少token
    bool table[MAX];                                  // 用index代表token的hash值 true代表有 for fast access
    int  table_chain[MAX][CHAIN_LENGTH];              // the chains stroring the head index of token
    int  table_chain_token_length[MAX][CHAIN_LENGTH]; // the chains stroring the length of token
    int  table_chain_max_idx[MAX];                    // the max index of the chain

    // store the hash values obtained from given tokens.
    // find_similar_function()    : tokens are given by mails' content and subject
    // expression_match_function(): tokens are given by testing data
    int token_list[100256];
} hashtable;

int AtoI(char x)
{
   if(x >= 'a' && x <= 'z')
    return x - 'a' + 10;
   else if (x >= 'A' && x <= 'Z')
    return x -'A' + 10;
   else if (x >= '0' && x <= '9')
    return x - '0';
   else
    return -1;
}

//unsigned long hash(char *input, int N)
//{
// unsigned long sum = 5381;
// for(int i=0; i < N; i++){
//  int c = AtoI(input[i]);
//  if(c < 0){
//   printf("Something Wrong\n");
//   return -1;
//  }
//  else{
//   sum = ((sum << 5) + sum) + c;
//  }
// }
// return sum&8191;
//}


void parse_and_hash(char *full_input, hashtable *store);
void find_similar_function(hashtable *mails_table, int mid, int n_mails, double threshold, int query_i);
void expression_match_function(hashtable *mails_table, char *expression, int query_i, int n_mails);
bool expression_match_calculate(bool *table, char *expression);
// The testdata only contains the first 100 mails (mail1 ~ mail100)
// and 2000 queries for you to debug.

int n_mails , n_queries;
mail *mails;
query *queries;

int main(void) {
 api.init(&n_mails, &n_queries, &mails, &queries);
 hashtable *mails_table = calloc(n_mails, sizeof(hashtable));
 for(int i = 0; i < n_mails; i++){
  parse_and_hash(mails[i].subject, mails_table+i);
  parse_and_hash(mails[i].content, mails_table+i);
 }
 
 for(int i = 0; i < n_queries; i++){
  if(queries[i].type == expression_match && queries[i].reward > 1.25){
   //expression_match_function(mails_table, queries[i].data.expression_match_data.expression, i, n_mails);
      //api.answer(queries[i].id, NULL, 0);
  }
  else if(queries[i].type == find_similar){
    find_similar_function(mails_table, queries[i].data.find_similar_data.mid, n_mails, 
                          queries[i].data.find_similar_data.threshold, i);
                //api.answer(queries[i].id, NULL, 0);
  }
  else{
   // Do something
  }
 }
 /*
 for(int i = 0; i < n_mails; i++)
 {
  printf("token_num:%d\n", mails_table[i].token_num);
  for(int j=0; j<mails_table[i].token_num; j++)
  {
   printf("%d ", mails_table[i].token_list[j]);
  }
  puts("check");
  for(int j=0; j<mails_table[i].token_num; j++)
  {
   printf("%d ", mails_table[i].table[mails_table[i].token_list[j]]);
  }

 }
 */
 free(mails_table);
   return 0;
}

bool stringCompare( int chain[], int max_idx_chain, char *full_input, int current_index_full_input,
                    int token_length, int table_chain_token_length[] ) 
{

  // loop through all indices smaller than `max_idx_chain` in chain
  for( int idx_chain=0;idx_chain<max_idx_chain;idx_chain++ ){

    int i = 0;

    // the head char of the previous token at `idx_chain` in chain
    char a = full_input[chain[idx_chain]];

    // the head char of current token
    char b = full_input[current_index_full_input];

    // we compare the current token and the previous one in char-by-char manner
    while( table_chain_token_length[idx_chain] == token_length && a == b && i+1<token_length ){

      i++;

      a = full_input[chain[idx_chain+i]];
      b = full_input[current_index_full_input+i];

    }

    if(i+1==token_length)  return true;
    else                   return false;
  }
}

//解析token並轉成hash值 存到hashtable裡
void parse_and_hash(char *full_input, hashtable *store)
{
 unsigned long sum = 53; //random seed
 bool start = false; //是否有在計算hash
 int i = 0;
 char a;
 int current_index_full_input = 0;
 int token_length = 0;
 int max_idx_chain = 0;

 while(a = *full_input++){ //遇到\0停止
  int c = AtoI(a); 

  // invalid charactors i.e. !([0-9][a-z][A-Z])
  if(c < 0){

   // we only store the hash values when the `sum` has been accumulated,
   // by doing so we can avoid consecutive invalid charactors i.e. !([0-9][a-z][A-Z])
   if(start){

    start = false;
    // if the chain has space for storing head index of token,
    // we store the hash values into table[];
    // otherwise, we simply drop and exmine the next token
    if(store->table_chain_max_idx[sum%MAX] < CHAIN_LENGTH-1)
    {
      // We do not store duplicate token into table[] and token_list[]
      if (stringCompare(store->table_chain[sum%MAX], max_idx_chain, full_input,
                        current_index_full_input,    token_length,  store->table_chain_token_length[sum%MAX]))
      {
        // make the (sum%MAX)-th element to be true
        store->table[sum%MAX] = true;

        // store hash values into token_list[]
        store->token_list[store->token_num++] = sum%MAX; 

        // store the head index of token into table_chain[][]
        max_idx_chain                                           = store->table_chain_max_idx[sum%MAX];
        store->table_chain[sum%MAX][++max_idx_chain]            = current_index_full_input - token_length;
        store->table_chain_token_length[sum%MAX][max_idx_chain] = token_length;
      }
    }

    // reset `sum` and `token_length`
    sum          = 53; 
    token_length = 0;
   }
  }
  else{
   start = true;
   sum = ((sum << 5) + sum) + c; // accumulation
   token_length++;
  }

  current_index_full_input++;
 }

 if(start){ //遇到\0後檢查最後一批hash是否要存入
  if( store->table_chain_max_idx[sum%MAX] < CHAIN_LENGTH-1){
   max_idx_chain = store->table_chain_max_idx[sum%MAX];
   store->table[sum%MAX] = true;
   store->token_list[store->token_num++] = sum%MAX;
   store->table_chain[sum%MAX][++max_idx_chain] = current_index_full_input - token_length;
  }
   
 }
}


void find_similar_function(hashtable *mails_table, int mid, int n_mails, double threshold, int query_i)
{
 int answer[n_mails];
 int answer_length = 0;
 double token_mid_num = mails_table[mid].token_num;

 for(int i=0; i < n_mails; i++){

  double token_i_num = mails_table[i].token_num;
  double denominator = token_i_num + token_mid_num;
  double numerator = 0;

  if(i == mid)                                                                                 continue;
  if(((token_i_num/token_mid_num) < threshold || ((token_mid_num/token_i_num) < threshold)))   continue;

  for(int j=0; j < token_mid_num; j++){
   if(mails_table[i].table[mails_table[mid].token_list[j]]){
      if (stringCompare(mails_table[i].table_chain[j], mails_table[i].table_chain_max_idx[j], full_input,
                        current_index_full_input, token_length, mails_table[i].table_chain_token_length[j]))
         numerator++;
   }
  }

  if((numerator/(denominator-numerator)) >= threshold)       answer[answer_length++] = i;

 }

 api.answer(queries[query_i].id, answer, answer_length);

 /*
 for(int i=0; i<answer_length; i++)
  printf("%d ", answer[i]);
 puts("");
 */
}


bool expression_match_calculate(bool *table, char *expression) // test data (crazay)|(kissi)|((coaxial)&(gym)&(izabalensis))|(gorenjska)
{
 bool bool_stack[2048];
 int operator_stack[2048];
 int bool_position = 0;
 int operator_position = 0;
 unsigned long hash = 5381;
 bool isCounting = false;
 char c;

 while(c = *expression++){
  int b = 0;
  if(c == ')') 
   b = 35;
  if(c == '(') 
   b = 30;
  if(c == '!') 
   b = 25;
  if(c == '&') 
   b = 20;
  if(c == '|') 
   b = 15;
  if(b != 0)
  {
   if(isCounting)
   {
    isCounting = false;
    bool_stack[bool_position++] = table[hash%MAX];
    hash = 5381;
   }
   if(b == 35)
   {
    while(operator_position > 0 && operator_stack[operator_position-1] != 30)
    {
     int opt_pop = operator_stack[--operator_position];
     if(opt_pop == 25)
      bool_stack[bool_position-1] = !(bool_stack[bool_position-1]);
     if(opt_pop == 20)
     {
      bool one = bool_stack[--bool_position];
      bool two = bool_stack[--bool_position];
      bool_stack[bool_position++] = (one && two);
     }
     if(opt_pop == 15)
     {
      bool one = bool_stack[--bool_position];
      bool two = bool_stack[--bool_position];
      bool_stack[bool_position++] = (one || two);
     }
    }
    operator_position--;
   }
   else if(b == 30)
    operator_stack[operator_position++] = b;
   else if(bool_position <= 0||operator_position <= 0 || operator_stack[operator_position-1] == 30 || b > operator_stack[operator_position-1])
    operator_stack[operator_position++] = b;
   else
   {
    while(operator_position > 0 && b <= operator_stack[operator_position-1] && operator_stack[operator_position-1] != 30)
    {
     int opt_pop = operator_stack[--operator_position];
     if(opt_pop == 25)
      bool_stack[bool_position-1] = !(bool_stack[bool_position-1]);
     if(opt_pop == 20)
     {
      bool one = bool_stack[--bool_position];
      bool two = bool_stack[--bool_position];
      bool_stack[bool_position++] = (one && two);
     }
     if(opt_pop == 15)
     {
      bool one = bool_stack[--bool_position];
      bool two = bool_stack[--bool_position];
      bool_stack[bool_position++] = (one || two);
     }
    }
    operator_stack[operator_position++] = b;
   }

  }
  else
  {
   isCounting = true;
   b = AtoI(c);
   hash = ((hash << 5) + hash) + b;
  }
 }

 if(isCounting) 
  bool_stack[bool_position++] = table[hash%MAX];
 while(operator_position > 0)
 {
  int opt_pop = operator_stack[--operator_position];
  if(opt_pop == 25)
   bool_stack[bool_position-1] = !(bool_stack[bool_position-1]);
  if(opt_pop == 20)
  {
   bool one = bool_stack[--bool_position];
   bool two = bool_stack[--bool_position];
   bool_stack[bool_position++] = (one && two);
  }
  if(opt_pop == 15)
  {
   bool one = bool_stack[--bool_position];
   bool two = bool_stack[--bool_position];
   bool_stack[bool_position++] = (one || two);
  }
 }
 return bool_stack[bool_position-1];
}


void expression_match_function(hashtable *mails_table, char *expression, int query_i, int n_mails)
{
 int answer[n_mails];
 int answer_length = 0;
 for(int i=0; i < n_mails; i++)
 {
  if(expression_match_calculate(mails_table[i].table, expression))
   answer[answer_length++] = i;
 }
 api.answer(queries[query_i].id, answer, answer_length);
}
