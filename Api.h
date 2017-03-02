std::vector<CTinyJS*> scripts;
std::vector<std::string> mods;
std::vector<std::string> paths;
std::string dump = "";
GuiData*gd;
Level*level;
MinecraftClient*mc;
LocalPlayer*lp;
Minecraft*minecraft;
Vibration*vibration;
Player*_player;
int entityId = 0;
#define Var CScriptVar
Var*var;
Vec3*_vec3;
Vec3*__vec3;
BlockPos*_blockpos;
EntityID*mbid = new EntityID();
std::vector<Font*> fonts;
map<Font*,float> txt_xmap;
map<Font*,float> txt_ymap;
map<Font*,std::string> txt_str;

Item*item;
bool canNewLevel = true;
std::vector<Item*> itemsToSetAttackDamage;
std::vector<int> itemsAttackDamage;
std::vector<int> idsToSetFuel;
std::vector<int> valuesToSetBurnDur;
std::vector<Entity*> entitiesToChested;
std::vector<bool> boolsToChested;
#define getString(name) var->getParameter(name)->getString()
#define getBool(name) var->getParameter(name)->getBool()
#define getInt(name) var->getParameter(name)->getInt()
#define getFloat(name) var->getParameter(name)->getDouble()
#define getArray(name) var->getParameter(name)->getArray()
bool isPreventedDefault;

struct Api{
	static void makeAndFixDumpStringData(const std::string& funcname,const std::string& params){
     	if(dump.find(funcname)==std::string::npos){
	     	dump += "\n"+funcname+"("+params+");";
		}
	}
	
	static void _makeAndFixDumpStringData(const std::string& funcname){
		if(dump.find(funcname)==std::string::npos){
	    	dump += "\n"+funcname+"();";
		}
	}
	
	static void prepare(){
	}
	
	static void add(const std::string &funcname,const std::string&params, JSCallback ptr,CTinyJS*js){
		makeAndFixDumpStringData(funcname,params);
	    create("sdcard/dump.txt",dump.c_str());
	    js->addNative("function "+funcname+"("+params+")",ptr,js);
	}
	
	static void add(const std::string &funcname, JSCallback ptr,CTinyJS*js){
		_makeAndFixDumpStringData(funcname);
		create("sdcard/dump.txt",dump.c_str());
	    js->addNative("function "+funcname+"()",ptr,js);
	}
	
};

void st1(Var*v,void*data){
	isPreventedDefault = true;
}

void e0(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(toStr(entity->entityType+entity->typeId+entity->id)));
}

void e1(Var*v,void*data){
	var = v;
	v->setReturnVar(new Var(mbid->getId(_player)));
}

void g0(Var*v,void*data){
	var = v;
	gd->displaySystemMessage(getString("string"));
}

void g1(Var*v,void*data){
	var = v;
	gd->showPopupNotice(getString("string"),getString("string2"));
}

void g2(Var*v,void*data){
	var = v;
	Font* font = (Font*)mc->getFont();
	txt_str[font] = getString("string");
	txt_xmap[font] = getInt("int");
	txt_ymap[font] = getInt("int2");
	fonts.push_back(font);
}

void m1(Var*v,void*data){
	var = v;
	v->setReturnVar(new Var(minecraft->isOnlineClient()));
}

void m2(Var*v,void*data){
	var = v;
	create(getString("string").c_str(),getString("string2").c_str());
}

void m3(Var*v,void*data){
	var = v;
	v->setReturnVar(new Var(read(getString("string").c_str())));
}

void m4(Var*v,void*data){
	var = v;
	v->setReturnVar(new Var(fileExists(getString("string").c_str())));
}

void m5(Var*v,void*data){
	var = v;
	createFolder(getString("string"));
}

void e2(Var*v,void*data){
	var = v;
	int eid = getInt("entity");
    Entity*entity = mbid->getEntity(eid);
    entity->jumpFromGround();
}

void e3(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->setSneaking(getBool("bool"));
}

void e4(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->setSprinting(getBool("bool"));
}

void e5(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->getNameTag()));
}

void e6(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isSurfaceMob()));
}

void e7(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isSneaking()));
}

void e8(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isSprinting()));
}

void e9(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->getHealth()));
}

void e10(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->getMaxHealth()));
}

void e11(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->serializationSetHealth(getInt("int"));
}

void e12(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->_doSprintParticleEffect();
}

void e13(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->_isHeadInWater()));
}

void e14(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->setSurfaceMob(getBool("bool"));
}

void e15(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->setInvisible(getBool("bool"));
}

void e16(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isInvisible()));
}

void e17(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->_isPersistent()));
}

void e18(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->wantsToBeJockey()));
}

void e19(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->setWantsToBeJockey(getBool("bool"));
}

void e20(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->setFlightSpeed(getInt("float"));
}

void e21(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->setSpeed(getInt("float"));
}

void e22(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->getFlightSpeed()));
}

void e23(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->getSpeed()));
}

void e24(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->outOfWorld();
}

void e25(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->ate();
}

void e26(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->setOnFire(getInt("int"));
}

void e27(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->swing();
}

void e28(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->heal(getInt("int"));
}

void  e29(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->hurt(*new EntityDamageSource("yeah"),getInt("int"),true,true);
}

void e30(Var*v,void*data){
	var = v;
	int pid = mbid->getId((Player*)level->getPlayer(getString("string")));
	v->setReturnVar(new Var(pid));
}

void e31(Var*v,void*data){
	var = v;
	Entity*entity = mbid->getEntity(getInt("entity"));
	entity->causeFallDamage(getInt("int"));
}

void  e32(Var*v,void*data){
	var = v;
	Entity* entity1 = mbid->getEntity(getInt("entity"));
	Entity* entity2 = mbid->getEntity(getInt("entity2"));
	if(entity1!=NULL&&entity2!=NULL){
    	entity1->setTarget(entity2);
	}
}

void  e33(Var*v,void*data){
	var = v;
    Entity* entity1 = mbid->getEntity(getInt("entity"));
	Entity* entity2 = mbid->getEntity(getInt("entity2"));
	entity1->doHurtTarget(entity2);
}

void  e34(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->setCarriedItem(*new ItemInstance(getInt("int"),getInt("int2"),getInt("int3")));
}

void  e35(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isLookingAtAnEntity()));
}

void e36(Var*v,void*data){
	var = v;
    Entity* entity1 = mbid->getEntity(getInt("entity"));
	Entity* entity2 = mbid->getEntity(getInt("entity2"));
	entity1->lookAt(entity2,getInt("int"),getFloat("int2"));
}

void e37(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->setRot(Vec2{getInt("int"),getInt("int2")});
}

void  e38(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(((Vec2*)entity->getRotation())->x));
}

void  e39(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(((Vec2*)entity->getRotation())->y));
}

void  e40(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(((Vec3*)entity->getPos())->x));
}

void  e41(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(((Vec3*)entity->getPos())->y));
}

void  e42(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(((Vec3*)entity->getPos())->z));
}

void  e43(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->setNameTag(getString("string"));
}

void  e44(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isRide()));
}

void  e45(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	Entity* entity2 = mbid->getEntity(getInt("entity2"));
	v->setReturnVar(new Var(entity->isRider(*entity2)));
}

void  e46(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isOnFire()));
}

void  e47(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isAutonomous()));
}

void  e48(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->setPersistent();
}

void  e49(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isInWaterOrRain()));
}

void  e50(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	Entity* entity2 = mbid->getEntity(getInt("entity2"));
	entity->killed(entity2);
}

void  e51(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	Entity* entity2 = mbid->getEntity(getInt("entity2"));
	entity->addRider(*entity2);
}

void  e52(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	Entity* entity2 = mbid->getEntity(getInt("entity2"));
	entity->positionRider(*entity2);
}

void  e53(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isInWater()));
}

void  e54(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isInWall()));
}

void  e55(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isInLove()));
}

void  e56(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isInLava()));
}

void  e57(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isBaby()));
}

void  e58(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isSitting()));
}

void  e59(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isTame()));
}

void  e60(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	Entity* entity2 = mbid->getEntity(getInt("entity2"));
	entity->setInLove(entity2);
}

void  e61(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->setCharged(getBool("bool"));
}

void  e62(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->setPowered(getBool("bool"));
}

void  e63(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isPushableByPiston()));
}

void  e64(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->setSaddle(getBool("bool"));
}

void  e65(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isCharged()));
}

void  e66(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isInWorld()));
}

void  e67(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isPowered()));
}

void  e68(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isSheared()));
}

void  e69(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->hasSaddle()));
}

void  e70(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isChested()));
}

void  e71(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isAngry()));
}

void  e72(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->isPickable()));
}

void e73(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->setNameTagVisible(getBool("bool"));
}

void e74(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	v->setReturnVar(new Var(entity->canShowNameTag()));
}

void e75(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->setSitting(getBool("bool"));
}

void e76(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->addEffect(*new MobEffectInstance(getInt("int"),getInt("int2"),getInt("int3")));
}

void e77(Var*v,void*data){
	var = v;
    Entity* entity = mbid->getEntity(getInt("entity"));
	entity->remove();
}

void e78(Var*v,void*data){
	var = v;
	int eid = getInt("entity");
	if(mbid->isValid(eid)){
		var->setReturnVar(new Var(true));
	}else{
		var->setReturnVar(new Var(false));
	}
}

void  p1(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	Entity* entity = mbid->getEntity(getInt("entity"));
	player->_touch(*entity);
}

void p2(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	player->openInventory();
}

void p3(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	player->eat(*new ItemInstance(getInt("int"),getInt("int2"),getInt("int3")));
}

void p4(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	player->eat(getInt("int"),getFloat("float"));
}

void p5(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	Entity* entity = mbid->getEntity(getInt("entity"));
	player->attack(*entity);
}

void p6(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	v->setReturnVar(new Var(player->canStartSleepInBed()));
}

void  p7(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	player->startSleepInBed(*new BlockPos(getFloat("float"),getFloat("float2"),getFloat("float3")));
}

void  p8(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	player->drop(*new ItemInstance(getInt("int"),getInt("int2"),getInt("int3")),getBool("bool"));
}

void  p9(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	v->setReturnVar(new Var(((ItemInstance*)player->getSelectedItem())!=NULL?((ItemInstance*)player->getSelectedItem())->getId():-1));
}

void  p10(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	player->setPlayerGameType((GameType)getInt("int"));
	mc->setGameMode((GameType)getInt("int"));
}

void  p11(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	v->setReturnVar(new Var(player->getGameModeString()));
}

void  p12(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	Entity*entity = mbid->getEntity(getInt("entity"));
	player->_crit(*entity);
}

void  p13(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	Entity*entity = mbid->getEntity(getInt("entity"));
	player->interact(*entity);
}

void  p14(Var*v,void*data){
	var = v;
    Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	v->setReturnVar(new Var(player->getXpNeededForNextLevel()));
}

void  p15(Var*v,void*data){
	var = v;
    Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	v->setReturnVar(new Var(player->hasOpenContainer()));
}

void  p16(Var*v,void*data){
	var = v;
    Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	((MinecraftClient*)player->getMinecraftClient())->handleDestoryOrAttackButtonPress();
}

void  p17(Var*v,void*data){
	var = v;
    Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	((MinecraftClient*)player->getMinecraftClient())->handleBuildOrInteractButtonPress();
}

void  p18(Var*v,void*data){
	var = v;
    Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	((MinecraftClient*)player->getMinecraftClient())->handleDropAllItemsButtonPress();
}

void  p19(Var*v,void*data){
	var = v;
    Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	player->chat(getString("string"));
}

void  p20(Var*v,void*data){
	var = v;
    Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	player->add(*new ItemInstance(getInt("int"),getInt("int2"),getInt("int3")));
}

void p21(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	Inventory*inventory = (Inventory*)player->getInventory();
	inventory->setContainerSize(getInt("int"));
}

void  i1(Var*v,void*data){
	var = v;
	Player* player = static_cast<Player*>(mbid->getEntity(getInt("player")));
	Item::mItems[getInt("int")]->releaseUsing(new ItemInstance(getInt("int2"),getInt("int3"),getInt("int4")),player,getInt("int5"));
}

void  i2(Var*v,void*data){
	var = v;
	Item*item = Item::mItems[getInt("int")];
	itemsToSetAttackDamage.push_back(item);
	itemsAttackDamage.push_back(getInt("int2"));
}

void  i3(Var*v,void*data){
	var = v;
	Item::addCreativeItem(getInt("int"),getInt("int2"));
}

void  i4(Var*v,void*data){
	var = v;
	idsToSetFuel.push_back(getInt("int"));
	valuesToSetBurnDur.push_back(getInt("int2"));
}

void i5(Var*v,void*data){
	var = v;
	Item::mItems[getInt("int")]->setIcon(getString("string"),getInt("int2"));
}

int (*itemAttackDamageManager$)(Item*);
int (*itemAttackDamageManager2$)(ItemInstance*);


void i6(Var*v,void*data){
	var = v;
	v->setReturnVar(new Var((new ItemInstance(Item::mItems[getInt("int")]))->getAttackDamage()));
}

void i7(Var*v,void*data){
	var = v;
	Item*item = Item::mItems[getInt("int")];
	item->setCategory((CreativeItemCategory)getInt("int2"));
}

void i8(Var*v,void*data){
	var = v;
	Item*item = Item::mItems[getInt("int")];
	item->setMaxDamage(getInt("int2"));
}

void i9(Var*v,void*data){
	var = v;
	Item*item = Item::mItems[getInt("int")];
	item->setMaxStackSize(getInt("int2"));
}

void i10(Var*v,void*data){
	var = v;
	Item*item = Item::mItems[getInt("int")];
	item->setIsGlint(getBool("bool"));
}

void i11(Var*v,void*data){
	var = v;
	Item*item = Item::mItems[getInt("int")];
	item->_textMatch(getString("string"),getString("string2"),getBool("bool"));
}

void i12(Var*v,void*data){
	var = v;
	Item*item = Item::mItems[getInt("int")];
	item->setExplodable(getBool("bool"));
}

void i13(Var*v,void*data){
	var = v;
	Item*item = Item::mItems[getInt("int")] = new Item(getString("string"),getInt("int") - 4096);
	item->setIcon("stick",0);
	Item::addCreativeItem(getInt("int"),0);
	item->initClientData();
}

void ll1(Var*v,void*data){
	var = v;
	BlockSource* region = ((BlockSource*)_player->getRegion());
	region->setBlockAndData(getInt("int"),getInt("int2"),getInt("int3"),BlockID{getInt("int4")},getInt("int5"),0);
}

void ll2(Var*v,void*data){
	var = v;
	BlockSource* region = ((BlockSource*)_player->getRegion());
	v->getReturnVar()->setString(toStr(region->getBlockID(*new BlockPos(getInt("int"),getInt("int2"),getInt("int3")))));
}

std::string getUUID(){
	vector<string> chars = {
		"1a","t7","2z","p3","i4","f2","zp","zz","ws","cc","cpp","pk","wt",
		"n2","k9","z2","x6","j2a","jd3","saz","sf","as","da","qp","id",
		"ll","p1","z3","z5","1zm","ns","dp","kd1","mn","az0","on4","db"
	};
	int size = chars.size();
	return string(chars[rand()%size-1]+chars[rand()%size-1]+chars[rand()%size-1]+chars[rand()%size-1]+chars[rand()%size-1]+chars[rand()%size-1]+chars[rand()%size-1]+chars[rand()%size-1]);
}

map<string,string> types;
map<string,vector<int>> iamap;
map<string,vector<string>> samap;

void array(Var*v,void*data){
	var = v;
	string uuid = getUUID();
	string type = getString("type");
	types[uuid] = type;
	if(type=="int"){
		iamap[uuid] = *new vector<int>();
	}else if(type=="string"){
		samap[uuid] = *new vector<string>();
	}
	var->getReturnVar()->setString(uuid);
}

void array_push(Var*v,void*data){
	var = v;
	string uuid = getString("arr");
	string type = types[uuid];
	if(type=="int"){
		int value = getInt("value");
		iamap[uuid].push_back(value);
	}else if(type=="string"){
		string value = getString("value");
		samap[uuid].push_back(value);
	}
}

void array_get(Var*v,void*data){
	var = v;
	string uuid = getString("arr");
	string type = types[uuid];
	int index = getInt("index");
	if(type=="int"){
		var->getReturnVar()->setInt(iamap[uuid][index]);
	}else if(type=="string"){
		var->getReturnVar()->setString(samap[uuid][index]);
	}
}

void array_size(Var*v,void*data){
	var = v;
	string uuid = getString("arr");
	string type = types[uuid];
	if(type=="int"){
		var->getReturnVar()->setInt(iamap[uuid].size());
	}else if(type=="string"){
		var->getReturnVar()->setInt(samap[uuid].size());
	}
}

void array_removeByIndex(Var*v,void*data){
	var = v;
	string uuid = getString("arr");
	string type = types[uuid];
	if(type=="int"){
		iamap[uuid].erase(iamap[uuid].begin()+getInt("index"));
	}else if(type=="string"){
		samap[uuid].erase(samap[uuid].begin()+getInt("index"));
	}
}

void array_removeByObject(Var*v,void*data){
	var = v;
	string uuid = getString("arr");
	string type = types[uuid];
	if(type=="int"){
		for(int i = 0;i<iamap[uuid].size();i++){
			if(iamap[uuid][i]==getInt("value")){
				iamap[uuid].erase(iamap[uuid].begin()+i);
			}
		}
	}else if(type=="string"){
		for(int i = 0;i<samap[uuid].size();i++){
			if(samap[uuid][i]==getString("value")){
				samap[uuid].erase(samap[uuid].begin()+i);
			}
		}
	}
}

void array_removeLast(Var*v,void*data){
	var = v;
	string uuid = getString("arr");
	string type = types[uuid];
	if(type=="int"){
		iamap[uuid].erase(iamap[uuid].begin()+iamap[uuid].size()-1);
	}else if(type=="string"){
		samap[uuid].erase(samap[uuid].begin()+samap[uuid].size()-1);
	}
}
