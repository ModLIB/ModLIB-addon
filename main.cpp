#include <jni.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>
#include <math.h>
#include <sstream>
#include <cmath>
#include <chrono>
#include <map>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "substrate.h"
#include "classes.h"
#include "TinyJS.h"
#include "TinyJS_Functions.h"
#include "TinyJS_MathFunctions.h"
#include "Utils.h"
#include "Api.h"

int timeToRegisterOwnPlayer = 0;

void (*playerTick$)(Player*);
void playerTick(Player*player){
	timeToRegisterOwnPlayer++;
	if(timeToRegisterOwnPlayer==1){
		_player = player;
	}
	mbid->putId(player,rand()%100000);
	level = (Level*)player->getLevel();
	lp = (LocalPlayer*)level->getLocalPlayer();
	mc = (MinecraftClient*)lp->getMinecraftClient();
	gd = (GuiData*)mc->getGuiData();
	try{
		for(CTinyJS*js : scripts){
	      	js->execute("modTick();");
		}
	}catch(void*e){}
	if(isPreventedDefault){
		isPreventedDefault = false;
    	return;
	}else{
		return playerTick$(player);
	}
}

void (*cminecraft$)(Minecraft*,GameCallbacks&, SkinInfoFactory&, Vibration&, SoundPlayer&, minecraft::api::Api&, Whitelist const&, OpsList const&, std::string const&, std::chrono::duration<long long, std::ratio<1ll,1ll> >, MinecraftEventing&);
void cminecraft(Minecraft*mine,GameCallbacks&gamecallbacks, SkinInfoFactory&skinfac, Vibration&vib, SoundPlayer&soundp, minecraft::api::Api&mcapi, Whitelist const&whtlist, OpsList const&oplist, std::string const&somestr, std::chrono::duration<long long, std::ratio<1ll,1ll> >chron, MinecraftEventing&mce){
	minecraft = mine;
	vibration = &vib;
	cminecraft$(mine,gamecallbacks,skinfac,vib,soundp,mcapi,whtlist,oplist,somestr,chron,mce);
}

static void (*attack$)(Player*,Entity&);
static void attack(Player*player,Entity&entity){
	try{
		for(CTinyJS*js : scripts){
	    	js->execute("attackHook("+toStr(mbid->getId(player))+","+toStr(mbid->getId(&entity))+");");
		}
	}catch(void*data){}
	try{
	if(isPreventedDefault){
		isPreventedDefault = false;
    	return;
	}else{
		return attack$(player,entity);
	}
	}catch(void*data){}
}

void (*useItemOn$)(GameMode*,Player&, ItemInstance*, BlockPos const&, signed char, Vec3 const&);
void useItemOn(GameMode*gamemode,Player&player, ItemInstance*iteminstance, BlockPos const&blockpos, signed char id, Vec3 const& vec3){
	try{
		std::string x = toStr(blockpos.x);
		std::string y = toStr(blockpos.y);
		std::string z = toStr(blockpos.z);
		for(CTinyJS*js : scripts){
	    	js->execute("useItem("+x+","+y+","+z+","+toStr((iteminstance!=NULL?iteminstance->getId():-1))+");");
		}	
		}catch(CScriptException*e){}
	if(isPreventedDefault){
		isPreventedDefault = false;
    	return;
	}else{
		useItemOn$(gamemode,player,iteminstance,blockpos,id,vec3);
	}
}


void (*setSize$)(Entity*,float,float);
void setSize(Entity*entity,float x,float y){
	setSize$(entity,x,y);
	entityId++;
	mbid->putId(entity,entityId);
	try{
		for(CTinyJS*js : scripts){
	    	js->execute("addedEntity("+toStr(mbid->getId(entity))+");");
		}
	}catch(void*data){}
	if(isPreventedDefault){
		isPreventedDefault = false;
    	return;
	}else{
		return setSize$(entity,x,y);
	}
}

void (*_remove$)(Entity*);
void _remove(Entity*entity){
	try{
		for(CTinyJS*js : scripts){
			js->execute("removedEntity("+toStr(mbid->getId(entity))+");");
		}
	}catch(void*data){}
	mbid->remove(entity);
	if(isPreventedDefault){
		isPreventedDefault = false;
    	return;
	}else{
		return _remove$(entity);
	}
}

void (*leaveGame$)(MinecraftClient*,bool);
void leaveGame(MinecraftClient*mc,bool someboolean){
	canNewLevel = true;
	mbid->clear();
	timeToRegisterOwnPlayer = 0;
	try{
		for(CTinyJS*js : scripts){
	    	js->execute("leaveGame();");
		}
	}catch(void*data){}
	if(isPreventedDefault){
		isPreventedDefault = false;
    	return;
	}else{
		return leaveGame$(mc,someboolean);
	}
}

int itemAttackDamageManager(Item*item){
	if(itemsToSetAttackDamage.size()>=1){
    	for(int i = 0;i<itemsToSetAttackDamage.size();i++){
	      	if(item==itemsToSetAttackDamage[i]){
		    	return itemsAttackDamage[i];
		    }
    	}
	}
	try{
		return itemAttackDamageManager$(item);
	}catch(void*aa){}
}

void (*heartRender$)(void*,MinecraftClient&, std::shared_ptr<UIControl>&, int, RectangleArea&);
void heartRender(void*data,MinecraftClient&mcclient, std::shared_ptr<UIControl>&uic, int idk, RectangleArea&rect){
	if(canNewLevel){
		/*BowItem* bow = static_cast<BowItem*>(Item::mItems[280]);
		bow->setIcon("sword",1);*/
		try{
			for(CTinyJS*js : scripts){
		    	js->execute("newLevel();");
			}
		}catch(void*data){}
		canNewLevel = false;
	}
	if(isPreventedDefault){
		isPreventedDefault = false;
    	return;
	}else{
		return heartRender$(data,mcclient,uic,idk,rect);
	}
}

void registerApiMethods(CTinyJS*js){
	Api::add("array","type",array,js);
	Api::add("array_push","arr,value",array_push,js);
	Api::add("array_get","arr,index",array_get,js);
	Api::add("array_size","arr",array_size,js);
	Api::add("array_removeByIndex","arr,index",array_removeByIndex,js);
	Api::add("array_removeByObject","arr,value",array_removeByObject,js);
	Api::add("array_removeLast","arr",array_removeLast,js);
	Api::add("preventDefault",st1,js);
	Api::add("Gui.clientMessage","string",g0,js);
	Api::add("Gui.showPopupNotice","string,string2",g1,js);
	Api::add("Gui.drawText","string,int,int2",g2,js);
	Api::add("ModLIB.isOnlineClient",m1,js);
	Api::add("ModLIB.fileCreate","string,string2",m2,js);
	Api::add("ModLIB.fileRead","string",m3,js);
	Api::add("ModLIB.fileExists","string",m4,js);
	Api::add("ModLIB.createFolder","string",m5,js);
	Api::add("Entity.getEntityTypeId","entity",e0,js);
	Api::add("Entity.getPlayer",e1,js);
	Api::add("Entity.jump","entity",e2,js);
	Api::add("Entity.setSneaking","entity,bool",e3,js);
	Api::add("Entity.setSprinting","entity,bool",e4,js);
	Api::add("Entity.getNameTag","entity",e5,js);
	Api::add("Entity.isSurface","entity",e6,js);
	Api::add("Entity.isSneaking","entity",e7,js);
	Api::add("Entity.isSprinting","entity",e8,js);
	Api::add("Entity.getHealth","entity",e9,js);
	Api::add("Entity.getMaxHealth","entity",e10,js);
	Api::add("Entity.setHealth","entity,int",e11,js);
	Api::add("Entity.doSprintParticle","entity",e12,js);
	Api::add("Entity.isHeadInWater","entity",e13,js);
	Api::add("Entity.setSurface","entity,bool",e14,js);
	Api::add("Entity.setInvisible","entity,bool",e15,js);
	Api::add("Entity.isInvisible","entity",e16,js);
	Api::add("Entity.isPersistent","entity",e17,js);
	Api::add("Entity.wantsToBeJockey","entity",e18,js);
	Api::add("Entity.setWantsToBeJockey","entity,bool",e19,js);
	Api::add("Entity.setFlightSpeed","entity,float",e20,js);
	Api::add("Entity.setSpeed","entity,float",e21,js);
	Api::add("Entity.getFlightSpeed","entity",e22,js);
	Api::add("Entity.getSpeed","entity",e23,js);
	Api::add("Entity.outOfWorld","entity",e24,js);
	Api::add("Entity.ate","entity",e25,js);
	Api::add("Entity.setOnFire","entity,int",e26,js);
	Api::add("Entity.swing","entity",e27,js);
	Api::add("Entity.heal","entity,int",e28,js);
	Api::add("Entity.hurt","entity,int",e29,js);
	Api::add("Entity.getPlayerByName","string",e30,js);
	Api::add("Entity.causeFallDamage","entity,int",e31,js);
	Api::add("Entity.setTarget","entity,entity2",e32,js);
	Api::add("Entity.doHurtTarget","entity,entity2",e33,js);
	Api::add("Entity.setCarriedItem","entity,int,int2,int3",e34,js);
	Api::add("Entity.isLookingAtAnEntity","entity",e35,js);
	Api::add("Entity.lookAt","entity,entity2,int,int2",e36,js);
	Api::add("Entity.setRot","entity,int,int2",e37,js);
	Api::add("Entity.getRotX","entity",e38,js);
	Api::add("Entity.getRotY","entity",e39,js);
	Api::add("Entity.getX","entity",e40,js);
	Api::add("Entity.getY","entity",e41,js);
    Api::add("Entity.getZ","entity",e42,js);
	Api::add("Entity.setNameTag","entity,string",e43,js);
	Api::add("Entity.isRide","entity",e44,js);
	Api::add("Entity.isRider","entity,entity2",e45,js);
	Api::add("Entity.isOnFire","entity",e46,js);
	Api::add("Entity.isAutonomous","entity",e47,js);
	Api::add("Entity.setPersistent","entity",e48,js);
	Api::add("Entity.isInWaterOrRain","entity",e49,js);
	Api::add("Entity.killed","entity,entity2",e50,js);
	Api::add("Entity.addRider","entity,entity2",e51,js);
	Api::add("Entity.positionRider","entity,entity2",e52,js);
	Api::add("Entity.isInWater","entity",e53,js);
	Api::add("Entity.isInWall","entity",e54,js);
	Api::add("Entity.isInLove","entity",e55,js);
	Api::add("Entity.isInLava","entity",e56,js);
	Api::add("Entity.isBaby","entity",e57,js);
	Api::add("Entity.isSitting","entity",e58,js);
	Api::add("Entity.isTame","entity",e59,js);
	Api::add("Entity.setInLove","entity,entity2",e60,js);
	Api::add("Entity.setCharged","entity,bool",e61,js);
	Api::add("Entity.setPowered","entity,bool",e62,js);
	Api::add("Entity.isPushableByPiston","entity",e63,js);
	Api::add("Entity.setSaddle","entity,bool",e64,js);
	Api::add("Entity.isCharged","entity",e65,js);
	Api::add("Entity.isInWorld","entity",e66,js);
	Api::add("Entity.isPowered","entity",e67,js);
	Api::add("Entity.isSheared","entity",e68,js);
	Api::add("Entity.hasSaddle","entity",e69,js);
	Api::add("Entity.isChested","entity",e70,js);
	Api::add("Entity.isAngry","entity",e71,js);
	Api::add("Entity.isPickable","entity",e72,js);
	Api::add("Entity.setNameTagVisible","entity,bool",e73,js);
	Api::add("Entity.canShowNameTag","entity",e74,js);
	Api::add("Entity.setSitting","entity,bool",e75,js);
	Api::add("Entity.addEffect","entity,int,int2,int3",e76,js);
	Api::add("Entity.remove","entity",e77,js);
	Api::add("Entity.isValid","entity",e78,js);
	Api::add("Player.touch","player,entity",p1,js);
	Api::add("Player.openInventory","player",p2,js);
	Api::add("Player.eat","player,int,int2,int3",p3,js);
	Api::add("Player._eat","player,int,float",p4,js);
	Api::add("Player.attack","player,entity",p5,js);
	Api::add("Player.canStartSleepInBed","player",p6,js);
	Api::add("Player.startSleepInBed","player,int,int2,int3",p7,js);
	Api::add("Player.drop","int,int2,int3,bool",p8,js);
	Api::add("Player.getCarriedItemId","player",p9,js);
	Api::add("Player.setGameMode","player,int",p10,js);
	Api::add("Player.getWorldTypeString","player",p11,js);
	Api::add("Player.critical","player,entity",p12,js);
	Api::add("Player.interact","player,entity",p13,js);
	Api::add("Player.getXpNeededForNextLevel","player",p14,js);
	Api::add("Player.hasOpenContainer","player",p15,js);
	Api::add("Player.destroyOrAttack","player",p16,js);
	Api::add("Player.buildOrInteract","player",p17,js);
	Api::add("Player.dropAllItems","player",p18,js);
	Api::add("Player.chat","player,string",p19,js);
	Api::add("Player.addItemInventory","player,int,int2,int3",p20,js);
	Api::add("Player.setInventorySize","player,int",p21,js);
	Api::add("Item.releaseUsing","int,int2,int3,int4,player,int5",i1,js);
	Api::add("Item.setAttackDamage","int,int2",i2,js);
	Api::add("Item.addCreativeItem","int,int2",i3,js);
	Api::add("Item.setIcon","int,string,int2",i5,js);
	Api::add("Item.getAttackDamage","int",i6,js);
	Api::add("Item.setCategory","int,int2",i7,js);
	Api::add("Item.setMaxDamage","int,int2",i8,js);
	Api::add("Item.setMaxStackSize","int,int2",i9,js);
	Api::add("Item.setIsGlint","int,bool",i10,js);
	Api::add("Item.setExplodable","int,bool",i12,js);
	Api::add("Level.setBlock","int,int2,int3,int4,int5",ll1,js);
	/*is crashing*/Api::add("Level.getBlock","int,int2,int3",ll2,js);
	/**/
}

void init(){
	for(std::string mod : mods){
		if(mod.find(".mod")!=std::string::npos){
	       	CTinyJS*script = new CTinyJS();
	    	registerApiMethods(script);
			registerMathFunctions(script);
			registerFunctions(script);
	     	try{
				if(fileExists("/data/user/0/net.zhuoweizhang.mcpelauncher/app_ptpatches/")){
					script->execute(read(std::string("/data/user/0/net.zhuoweizhang.mcpelauncher/app_ptpatches/"+mod).c_str()));
				}else if(fileExists("/data/user/0/net.zhuoweizhang.mcpelauncher.pro/app_ptpatches/")){
					script->execute(read(std::string("/data/user/0/net.zhuoweizhang.mcpelauncher.pro/app_ptpatches/"+mod).c_str()));
				}
	      	}catch(CScriptException*data){
	    		create("sdcard/error.txt",data->text.c_str());
	    	}
	     	scripts.push_back(script);
		}
	}
}

bool (*isFFI$)(void*,ItemInstance const*);
bool isFFI(void*data,ItemInstance const*iteminstance){
	if(idsToSetFuel.size()>=1){
	for(int i = 0;i<idsToSetFuel.size();i++){
		if(iteminstance->getId()==idsToSetFuel[i]){
			return true;
		}
	}
	}
	try{
	return isFFI$(data,iteminstance);
	}catch(void*data){
		
	}
}

void (*onLightningHit$)(Entity*);
void onLightningHit(Entity*entity){
	try{
		for(CTinyJS*js : scripts){
			js->execute("onLightningHit("+toStr(mbid->getId(entity))+");");
		}
	}catch(void*data){}
	if(isPreventedDefault){
		isPreventedDefault = false;
		return;
	}else{
		return onLightningHit$(entity);
	}
}

void (*onFailedTame$)(Entity*);
void onFailedTame(Entity*entity){
	try{
		for(CTinyJS*js : scripts){
			js->execute("onFailedTame("+toStr(mbid->getId(entity))+");");
		}
	}catch(void*data){}
	if(isPreventedDefault){
		isPreventedDefault = false;
		return;
	}else{
		return onFailedTame$(entity);
	}
}

void (*onKilledEntity$)(Player*, Entity*, Mob&, unsigned int);
void onKilledEntity(Player*killer, Entity*killed, Mob&mob, unsigned int yeah){
	try{
		for(CTinyJS*js : scripts){
			std::string krid = toStr(mbid->getId(killer));
			std::string kid = toStr(mbid->getId(&mob));
			js->execute("onKilledEntity("+krid+","+kid+","+toStr(yeah)+");");
		}
	}catch(void*data){}
	try{
	if(isPreventedDefault){
		isPreventedDefault = false;
		return;
	}else{
		return onKilledEntity$(killer,killed,mob,yeah);
	}
	}catch(void*data){}
}

void (*onHurtEntity$)(Entity*,EntityDamageSource const&, int, bool, bool);
void onHurtEntity(Entity*victim,EntityDamageSource const&dmgs, int dmg, bool idk, bool idk2){
	try{
		for(CTinyJS*js : scripts){
			std::string atid = toStr(mbid->getId((Entity*)dmgs.getEntity()));
			std::string vid = toStr(mbid->getId(victim));
			std::string dmg_ = toStr(dmg);
			js->execute("onHurtEntity("+atid+","+vid+","+dmg_+");");
		}
	}catch(void*data){}
	try{
	if(isPreventedDefault){
		isPreventedDefault = false;
		return;
	}else{
		return onHurtEntity$(victim,dmgs,dmg,idk,idk2);
	}
	}catch(void*data){}
}

void (*onTame$)(Entity*);
void onTame(Entity*tamed){
	try{
		for(CTinyJS*js : scripts){
			js->execute("onTame("+toStr(mbid->getId(tamed))+");");
		}
	}catch(void*data){}
	if(isPreventedDefault){
		isPreventedDefault = false;
		return;
	}else{
		return onTame(tamed);
	}
}

void (*onCrafted$)(Player*,ItemInstance const&);
void onCrafted(Player*player,ItemInstance const&itemi){
	try{
		for(CTinyJS*js : scripts){
			std::string id = toStr(itemi.getId());
			std::string dmg = toStr(itemi.getAuxValue());
			std::string pid = toStr(mbid->getId(player));
			js->execute("onCraftedItem("+id+","+dmg+","+pid+");");
		}
	}catch(void*data){}
	try{
	onCrafted$(player,itemi);
	}catch(void*dated){}
}

void (*destroyBlock$)(void*,Player&, BlockPos, signed char);
void destroyBlock(void*data,Player&player, BlockPos bp, signed char id){
	try{
		for(CTinyJS*js : scripts){
			std::string x = toStr(bp.x);
			std::string y = toStr(bp.y);
			std::string z = toStr(bp.z);
			js->execute("onDestroyBlock("+x+","+y+","+z+");");
		}
	}catch(void*data){}
	try{
		if(isPreventedDefault){
			isPreventedDefault = false;
			return;
		}else{
	    	destroyBlock$(data,player,bp,id);
		}
	}catch(void*data){}
}

void (*jumpFromGround$)(Entity*);
void jumpFromGround(Entity*entity){
	try{
		for(CTinyJS*js : scripts){
			js->execute("onJumpEntity("+toStr(mbid->getId(entity))+");");
		}
	}catch(void*data){}
	try{
	jumpFromGround$(entity);
	}catch(void*data){}
}

void (*onChat$)(GuiMessage&);
void onChat(GuiMessage&gm){
	try{
		for(CTinyJS*js : scripts){
			js->execute("chatHook('"+(&gm)->getMessage()+"');");
		}
	}catch(void*data){}
	try{
		return onChat$(gm);
	}catch(void*data){}
}

void (*onLangChanged$)(Font*,std::string const&);
void onLangChanged(Font*font,std::string const&lang){
	try{
		for(CTinyJS*js : scripts){
			js->execute("onLanguageChanged('"+lang+"');");
		}
	}catch(void*data){}
	onLangChanged$(font,lang);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	if(fileExists("/data/user/0/net.zhuoweizhang.mcpelauncher/app_ptpatches/")){
    	getdir("/data/user/0/net.zhuoweizhang.mcpelauncher/app_ptpatches/",mods);
	}
	else if(fileExists("/data/user/0/net.zhuoweizhang.mcpelauncher.pro/app_ptpatches/")){
    	getdir("/data/user/0/net.zhuoweizhang.mcpelauncher.pro/app_ptpatches/",mods);
	}
	init();
	Hook((void*)&Player::normalTick,(void*)&playerTick,(void**)&playerTick$);
	Hook((void*)&Player::attack,(void*)&attack,(void**)&attack$);
	Hook((void*)&GameMode::useItemOn,(void*)&useItemOn,(void**)&useItemOn$);
	Hook("_ZN9MinecraftC1ER13GameCallbacksR15SkinInfoFactoryR9VibrationR11SoundPlayerRN9minecraft3api3ApiERK9WhitelistRK7OpsListRKSsNSt6chrono8durationIxSt5ratioILx1ELx1EEEER17MinecraftEventing",(void*)&cminecraft,(void**)&cminecraft$);
	Hook((void*)&Entity::setSize,(void*)&setSize,(void**)&setSize$);
	Hook((void*)&Entity::remove,(void*)&_remove,(void**)&_remove$);
	Hook((void*)&MinecraftClient::leaveGame,(void*)&leaveGame,(void**)&leaveGame$);
	Hook((void*)&Item::getAttackDamage,(void*)&itemAttackDamageManager,(void**)&itemAttackDamageManager$);
	Hook((void*)&HudHeartRenderer::render,(void*)&heartRender,(void**)&heartRender$);
	//Hook((void*)&FurnaceBlockEntity::isFuel,(void*)&isFFI,(void**)&isFFI$);
	//Hook((void*)&Entity::onLightningHit,(void*)&onLightningHit,(void**)&onLightningHit$);
	//Hook((void*)&Entity::onFailedTame,(void*)&onFailedTame,(void**)&onFailedTame$);
	Hook((void*)&MinecraftEventing::fireEventMobKilled,(void*)&onKilledEntity,(void**)&onKilledEntity$);
	Hook((void*)&Entity::hurt,(void*)&onHurtEntity,(void**)&onHurtEntity$);
	//Hook((void*)&Entity::onTame,(void*)&onTame,(void**)&onTame$);
	Hook((void*)&GameMode::destroyBlock,(void*)&destroyBlock,(void**)&destroyBlock$);
	Hook((void*)&MinecraftEventing::fireEventItemCrafted,(void*)&onCrafted,(void**)&onCrafted$);
	Hook((void*)&Entity::jumpFromGround,(void*)&jumpFromGround,(void**)&jumpFromGround$);
	Hook((void*)&GuiData::_insertGuiMessage,(void*)&onChat,(void**)&onChat$);
	Hook((void*)&Font::onLanguageChanged,(void*)&onLangChanged,(void**)&onLangChanged$);
	return JNI_VERSION_1_2;
}
