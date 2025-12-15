void INT_IO(void){
   #use fast_io(A)
   #use fast_io(B)

   set_tris_A(0x0F);
   set_tris_B(0x03); // RB0, RB1は入力(1)、RB2～RB7は出力(0)

   return;
}