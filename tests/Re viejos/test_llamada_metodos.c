class test_class{
   float c;
   void alo(int x){
      x= x + 1;
   }

   void alo2(int x){
      alo();
      x=  alo() + 1;
   }

}
