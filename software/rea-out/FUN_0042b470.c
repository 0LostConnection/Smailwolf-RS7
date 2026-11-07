
void FUN_0042b470(void)

{
  int iVar1;
  undefined *this;
  int iVar2;
  undefined4 *this_00;
  undefined4 extraout_ECX;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  undefined4 uVar7;
  int *piVar8;
  int local_a4;
  int local_a0;
  undefined4 local_9c;
  int local_98;
  char local_94 [9];
  undefined4 local_8b [29];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0053638b;
  local_10 = ExceptionList;
  local_14 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_98 = 1;
  do {
    iVar5 = local_98;
    memset(local_94 + 1,0,0x7f);
    local_94[8] = (char)iVar5 + -1;
    local_94[0] = '\0';
    local_94[1] = 'U';
    local_94[2] = '\t';
    local_94[3] = -0x5b;
    local_94[4] = '\"';
    local_94[5] = ' ';
    local_94[6] = '\0';
    local_94[7] = '\0';
    local_8b[0] = 0x120;
    local_8b[1] = 0x220;
    local_8b[2] = 0x420;
    local_8b[3] = 0x820;
    local_8b[4] = 0x1020;
    local_8b[5] = 0x5521;
    local_8b[6] = 0x13821;
    local_8b[7] = 0xff3821;
    local_a4 = 0;
    local_a0 = 0;
    local_9c = 0;
    piVar8 = &local_a4;
    local_8 = 0;
    uVar7 = extraout_ECX;
    this = FUN_00401170();
    FUN_00407320(this,iVar5,uVar7,piVar8);
    iVar5 = local_a4;
    uVar3 = 0;
    uVar4 = local_a0 - local_a4 >> 2;
    if (uVar4 != 0) {
      if (uVar4 == 0) {
                    /* WARNING: Subroutine does not return */
        std::_Xout_of_range("invalid vector<T> subscript");
      }
      do {
        iVar1 = *(int *)(iVar5 + uVar3 * 4);
        if (iVar1 != 0) {
          iVar2 = *(int *)(iVar1 + 0xc);
          if (iVar2 == 4) {
            iVar2 = 4;
          }
          else if (iVar2 == 5) {
            iVar2 = 3;
          }
          else {
            iVar2 = iVar2 + -1;
          }
          FUN_00411550(iVar1,local_8b + iVar2);
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < uVar4);
    }
    pcVar6 = local_94;
    this_00 = FUN_00401200();
    FUN_0043be10(this_00,pcVar6);
    local_8 = 0xffffffff;
    FUN_0040fcc0(&local_a4);
    local_98 = local_98 + 1;
  } while (local_98 < 6);
  ExceptionList = local_10;
  __security_check_cookie(local_14 ^ (uint)&stack0xfffffffc);
  return;
}

