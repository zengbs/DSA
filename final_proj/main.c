#include "api.h"
#include <stdio.h>

// The testdata only contains the first 100 mails (mail1 ~ mail100)
// and 2000 queries for you to debug.


int n_mails, n_queries;
mail *mails;
query *queries;

int main(void) {
	api.init(&n_mails, &n_queries, &mails, &queries);

	for(int i = 0; i < n_queries; i++){

		if(queries[i].type == find_similar){

          printf("\nid: %d"       , mails[i].id);
          printf("\nFrom: %s"     , mails[i].from);
          printf("\nTo: %s"       , mails[i].to);
          printf("\nsubject: %s\n", mails[i].subject);
          printf("\ncontent: %s\n", mails[i].content);


		  api.answer(queries[i].id, NULL, 0);

        }

    }

  return 0;
}
