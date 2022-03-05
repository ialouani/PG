#include<stdio.h>
#include<stdlib.h>
#include"link.h"
#include<assert.h>
int main(){
  struct link* s1=link__empty();
  assert(s1==NULL);
  assert(link__first(s1)==NULL);
  struct lelement* s2=malloc(sizeof(*s2));
  s2->data=10;
  s2->next=s2;
struct lelement* s5=malloc(sizeof(*s5));
  s5->data=15;
  s5->next=s5;
  struct link* s4=malloc(sizeof(*s4));
  s4->head=s2;
  assert(s4!=NULL && link__first(s4)==s2);
  struct lelement *s3=malloc(sizeof(*s3));
  s3->data=20;
  s3->next=s2;
  assert(llm__is_end_mark(s3)==false);
  assert(llm__is_end_mark(s2)==true);
  assert(s3!=NULL);
  link__add_head(s4,s5);
  link__add_head(s4,s3);
  assert(s4->head==s3 && s3->next==s5 && s5->next==s2 && s2->next==s2);
  struct lelement *s10=link__remove_head(s4);
  assert(s10->data==20);
  assert(s10->next==s5);
  assert(s4->head==s5 && s5->next==s2 && s3->next==s5);
  assert(s4->head->next==s2);
  assert(s10->next==s5 && (s10->next->next)==s2);
  //struct lelement *s20=link__remove_head(NULL);
  struct lelement *s30=llm__next_2(s5);
  assert(s30==s2);
  link__add_after(s4,s5,s3);
  assert(s4->head==s5 && s5->next==s3 && s3->next==s2 && s2->next==s2);
  link__add_after(s4,s3,s10);
  assert(s4->head==s5 && s5->next==s3 && s3->next==s10 && s10->next==s2);
  assert(s2->next->next->next==s2);
  struct lelement* s100=link__remove_after(s4,s5);
  assert(s100->next==s4->head->next);
  struct lelement* s200=link__remove_after(s4,s5);
  assert(s100->next == s200);
  assert(s4->head==s5 && s5->next==s2 && s2->next==s2);
  assert(s200->next==s4->head->next);
  link__add_tail(s4,s10);
  link__add_tail(s4,s200);
  assert(s4->head==s5 && s5->next==s2 && s2->next==s10 && s10->next==s200);
  assert(s200->next==s200);
  link__remove_after(s4,s2);
  assert(s4->head==s5 && s5->next==s2 && s2->next==s200 && s200->next==s200);
  link__remove_tail(s4);
  link__remove_tail(s4);
  assert(s4->head==s5 && s5->next==s5);
  return 0;//TOUT est verifié!!!!!!!!!!
}
