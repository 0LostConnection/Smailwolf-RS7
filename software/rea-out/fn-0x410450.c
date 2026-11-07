void FUN_00410450(int param_1)

{
  int iVar1;
  int *piVar2;
  wchar_t *pwVar3;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00533b98;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004054f0(&local_14,(short *)&PTR_0054b37c);
  local_8 = 0;
  if (param_1 == 1) {
    FUN_00405eb0(&local_14,&DAT_0054c3f4,4);
  }
  else if (param_1 == 2) {
    FUN_00405eb0(&local_14,&DAT_0054c400,4);
  }
  else if (param_1 == 3) {
    FUN_00405eb0(&local_14,&DAT_0054c40c,3);
  }
  else {
    if (param_1 == 4) {
      pwVar3 = L"[发呆]";
    }
    else if (param_1 == 5) {
      pwVar3 = L"[得意]";
    }
    else if (param_1 == 6) {
      pwVar3 = L"[流泪]";
    }
    else if (param_1 == 7) {
      pwVar3 = L"[害羞]";
    }
    else if (param_1 == 8) {
      pwVar3 = L"[闭嘴]";
    }
    else if (param_1 == 9) {
      pwVar3 = L"[睡]";
    }
    else if (param_1 == 10) {
      pwVar3 = L"[大哭]";
    }
    else if (param_1 == 0xb) {
      pwVar3 = L"[尴尬]";
    }
    else if (param_1 == 0xc) {
      pwVar3 = L"[发怒]";
    }
    else if (param_1 == 0xd) {
      pwVar3 = L"[调皮]";
    }
    else if (param_1 == 0xe) {
      pwVar3 = L"[呲牙]";
    }
    else if (param_1 == 0xf) {
      pwVar3 = L"[惊讶]";
    }
    else if (param_1 == 0x10) {
      pwVar3 = L"[难过]";
    }
    else if (param_1 == 0x11) {
      pwVar3 = L"[囧]";
    }
    else if (param_1 == 0x12) {
      pwVar3 = L"[抓狂]";
    }
    else if (param_1 == 0x13) {
      pwVar3 = L"[吐]";
    }
    else if (param_1 == 0x14) {
      pwVar3 = L"[偷笑]";
    }
    else if (param_1 == 0x15) {
      pwVar3 = L"[愉快]";
    }
    else if (param_1 == 0x16) {
      pwVar3 = L"[白眼]";
    }
    else if (param_1 == 0x17) {
      pwVar3 = L"[傲慢]";
    }
    else if (param_1 == 0x18) {
      pwVar3 = L"[困]";
    }
    else if (param_1 == 0x19) {
      pwVar3 = L"[惊恐]";
    }
    else if (param_1 == 0x1a) {
      pwVar3 = L"[憨笑]";
    }
    else if (param_1 == 0x1b) {
      pwVar3 = L"[悠闲]";
    }
    else if (param_1 == 0x1c) {
      pwVar3 = L"[咒骂]";
    }
    else if (param_1 == 0x1d) {
      pwVar3 = L"[疑问]";
    }
    else if (param_1 == 0x1e) {
      pwVar3 = L"[嘘]";
    }
    else if (param_1 == 0x1f) {
      pwVar3 = L"[晕]";
    }
    else if (param_1 == 0x20) {
      pwVar3 = L"[衰]";
    }
    else if (param_1 == 0x21) {
      pwVar3 = L"[骷髅]";
    }
    else if (param_1 == 0x22) {
      pwVar3 = L"[敲打]";
    }
    else if (param_1 == 0x23) {
      pwVar3 = L"[再见]";
    }
    else if (param_1 == 0x24) {
      pwVar3 = L"[擦汗]";
    }
    else if (param_1 == 0x25) {
      pwVar3 = L"[抠鼻]";
    }
    else if (param_1 == 0x26) {
      pwVar3 = L"[鼓掌]";
    }
    else if (param_1 == 0x27) {
      pwVar3 = L"[坏笑]";
    }
    else if (param_1 == 0x28) {
      pwVar3 = L"[右哼哼]";
    }
    else if (param_1 == 0x29) {
      pwVar3 = L"[鄙视]";
    }
    else if (param_1 == 0x2a) {
      pwVar3 = L"[委屈]";
    }
    else if (param_1 == 0x2b) {
      pwVar3 = L"[快哭了]";
    }
    else if (param_1 == 0x2c) {
      pwVar3 = L"[阴险]";
    }
    else if (param_1 == 0x2d) {
      pwVar3 = L"[亲亲]";
    }
    else if (param_1 == 0x2e) {
      pwVar3 = L"[可怜]";
    }
    else if (param_1 == 0x2f) {
      pwVar3 = L"[笑脸]";
    }
    else if (param_1 == 0x30) {
      pwVar3 = L"[生病]";
    }
    else if (param_1 == 0x31) {
      pwVar3 = L"[脸红]";
    }
    else if (param_1 == 0x32) {
      pwVar3 = L"[破涕为笑]";
    }
    else if (param_1 == 0x33) {
      pwVar3 = L"[恐惧]";
    }
    else if (param_1 == 0x34) {
      pwVar3 = L"[失望]";
    }
    else if (param_1 == 0x35) {
      pwVar3 = L"[无语]";
    }
    else if (param_1 == 0x36) {
      pwVar3 = L"[嘿哈]";
    }
    else if (param_1 == 0x37) {
      pwVar3 = L"[捂脸]";
    }
    else if (param_1 == 0x38) {
      pwVar3 = L"[奸笑]";
    }
    else if (param_1 == 0x39) {
      pwVar3 = L"[机智]";
    }
    else if (param_1 == 0x3a) {
      pwVar3 = L"[皱眉]";
    }
    else if (param_1 == 0x3b) {
      pwVar3 = L"[耶]";
    }
    else if (param_1 == 0x3c) {
      pwVar3 = L"[吃瓜]";
    }
    else if (param_1 == 0x3d) {
      pwVar3 = L"[加油]";
    }
    else if (param_1 == 0x3e) {
      pwVar3 = L"[汗]";
    }
    else if (param_1 == 0x3f) {
      pwVar3 = L"[天啊]";
    }
    else if (param_1 == 0x40) {
      pwVar3 = L"[Emm]";
    }
    else if (param_1 == 0x41) {
      pwVar3 = L"[社会社会]";
    }
    else if (param_1 == 0x42) {
      pwVar3 = L"[旺柴]";
    }
    else if (param_1 == 0x43) {
      pwVar3 = L"[好的]";
    }
    else if (param_1 == 0x44) {
      pwVar3 = L"[打脸]";
    }
    else if (param_1 == 0x45) {
      pwVar3 = L"[哇]";
    }
    else if (param_1 == 0x46) {
      pwVar3 = L"[翻白眼]";
    }
    else if (param_1 == 0x47) {
      pwVar3 = L"[666]";
    }
    else if (param_1 == 0x48) {
      pwVar3 = L"[让我看看]";
    }
    else if (param_1 == 0x49) {
      pwVar3 = L"[叹气]";
    }
    else if (param_1 == 0x4a) {
      pwVar3 = L"[苦涩]";
    }
    else if (param_1 == 0x4b) {
      pwVar3 = L"[裂开]";
    }
    else if (param_1 == 0x4c) {
      pwVar3 = L"[嘴唇]";
    }
    else if (param_1 == 0x4d) {
      pwVar3 = L"[爱心]";
    }
    else if (param_1 == 0x4e) {
      pwVar3 = L"[心碎]";
    }
    else if (param_1 == 0x4f) {
      pwVar3 = L"[拥抱]";
    }
    else if (param_1 == 0x50) {
      pwVar3 = L"[强]";
    }
    else if (param_1 == 0x51) {
      pwVar3 = L"[弱]";
    }
    else if (param_1 == 0x52) {
      pwVar3 = L"[握手]";
    }
    else if (param_1 == 0x53) {
      pwVar3 = L"[胜利]";
    }
    else if (param_1 == 0x54) {
      pwVar3 = L"[抱拳]";
    }
    else if (param_1 == 0x55) {
      pwVar3 = L"[勾引]";
    }
    else if (param_1 == 0x56) {
      pwVar3 = L"[拳头]";
    }
    else if (param_1 == 0x57) {
      pwVar3 = L"[OK]";
    }
    else if (param_1 == 0x58) {
      pwVar3 = L"[合十]";
    }
    else if (param_1 == 0x59) {
      pwVar3 = L"[啤酒]";
    }
    else if (param_1 == 0x5a) {
      pwVar3 = L"[咖啡]";
    }
    else if (param_1 == 0x5b) {
      pwVar3 = L"[蛋糕]";
    }
    else if (param_1 == 0x5c) {
      pwVar3 = L"[玫瑰]";
    }
    else if (param_1 == 0x5d) {
      pwVar3 = L"[凋谢]";
    }
    else if (param_1 == 0x5e) {
      pwVar3 = L"[菜刀]";
    }
    else if (param_1 == 0x5f) {
      pwVar3 = L"[炸弹]";
    }
    else if (param_1 == 0x60) {
      pwVar3 = L"[便便]";
    }
    else if (param_1 == 0x61) {
      pwVar3 = L"[月亮]";
    }
    else if (param_1 == 0x62) {
      pwVar3 = L"[太阳]";
    }
    else if (param_1 == 99) {
      pwVar3 = L"[庆祝]";
    }
    else if (param_1 == 100) {
      pwVar3 = L"[礼物]";
    }
    else if (param_1 == 0x65) {
      pwVar3 = L"[红包]";
    }
    else if (param_1 == 0x66) {
      pwVar3 = L"[發]";
    }
    else if (param_1 == 0x67) {
      pwVar3 = L"[福]";
    }
    else if (param_1 == 0x68) {
      pwVar3 = L"[烟花]";
    }
    else if (param_1 == 0x69) {
      pwVar3 = L"[爆竹]";
    }
    else if (param_1 == 0x6a) {
      pwVar3 = L"[猪头]";
    }
    else if (param_1 == 0x6b) {
      pwVar3 = L"[跳跳]";
    }
    else if (param_1 == 0x6c) {
      pwVar3 = L"[发抖]";
    }
    else {
      if (param_1 != 0x6d) goto LAB_00410af0;
      pwVar3 = L"[转圈]";
    }
    FUN_004053e0(&local_14,pwVar3);
  }
LAB_00410af0:
  if (*(int *)(local_14 + -0xc) != 0) {
    piVar2 = FUN_00405df0((int *)(local_14 + -0x10));
    FUN_00410b50(piVar2 + 4);
  }
  local_8 = 0xffffffff;
  LOCK();
  piVar2 = (int *)(local_14 + -4);
  iVar1 = *piVar2;
  *piVar2 = *piVar2 + -1;
  UNLOCK();
  if (iVar1 == 1 || iVar1 + -1 < 0) {
    (**(code **)(**(int **)(local_14 + -0x10) + 4))();
  }
  ExceptionList = local_10;
  return;
}


