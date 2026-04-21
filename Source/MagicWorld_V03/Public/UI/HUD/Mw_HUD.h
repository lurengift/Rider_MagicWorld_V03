// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Mw_HUD.generated.h"

class UMw_AttributeSet_Base;
class UMw_AbilitySystemComponent;
class AMw_PlayerState_Base;
class UMw_WidgetController_Inventory;
class UMw_WidgetController_Overlay;
class UMw_UserWidget_Base;
class AMw_PlayerController_Base;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API AMw_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	
	// 初始化（在玩家角色中调用）
	//初始化控制层实例，将widget的控制层设置为初始化的实例，并且将其输出到屏幕
	UFUNCTION(BlueprintCallable, Category = "MagicWorld|UI")
	void InitOverlay(AMw_PlayerController_Base* MwPC, AMw_PlayerState_Base* MwPs, UMw_AbilitySystemComponent* MwAsc, UMw_AttributeSet_Base* MwAs);
	
	/**
	 * 获取叠加层小部件
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category = "MagicWorld|UI")
	UMw_UserWidget_Base* GetOverlayWidget();
	
	UMw_UserWidget_Base* ToggleInventory();
	
	void ToggleInventoryMenu();
	
	UFUNCTION(BlueprintCallable, Category = "MagicWorld|UI")
	UMw_UserWidget_Base* GetInventoryWidget();
	
	UMw_WidgetController_Inventory* GetWidgetController_InventoryMenu(const FWidgetControllerParams& WcParams);
private:
	// 控制器 
	TWeakObjectPtr<APlayerController> HUDOwingController;
	
	// Widget 实例（缓存）
	UPROPERTY()
	TObjectPtr<UMw_UserWidget_Base> OverlayWidget;      // 常驻HUD（血条、快捷栏等）
	UPROPERTY()
	TObjectPtr<UMw_UserWidget_Base> InventoryWidget;   // 背包界面
	
	// 蓝图指定的 Widget 类
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMw_UserWidget_Base> OverlayWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMw_UserWidget_Base> InventoryWidgetClass;

	// Controller 实例（缓存）
	UPROPERTY()
	TObjectPtr<UMw_WidgetController_Overlay> OverlayController;
	UPROPERTY()
	TObjectPtr<UMw_WidgetController_Inventory> InventoryController;

	// 库存界面是否显示
	bool IsShowingInventory = false;
	// 蓝图指定的 Controller 类
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMw_WidgetController_Overlay> OverlayControllerClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMw_WidgetController_Inventory> InventoryControllerClass;

	/**
	 * 创建OverlayWidget
	 * @param MwPC AMw_PlayerController_Base
	 * @param MwPs AMw_PlayerState_Base
	 * @param MwAsc UMw_AbilitySystemComponent
	 * @param MwAs UMw_AttributeSet_Base
	 */
	void CreateOverlayWidget(AMw_PlayerController_Base* MwPC, AMw_PlayerState_Base* MwPs,
	                         UMw_AbilitySystemComponent* MwAsc, UMw_AttributeSet_Base* MwAs);


	/**
	 * 初始化WidgetController_Overlay控制器，并将回调绑定到依赖项
	 * @param WcParams FWidgetControllerParams
	 * @return UMw_WidgetController_Overlay
	 */
	UMw_WidgetController_Overlay* GetWidgetController_Overlay(const FWidgetControllerParams& WcParams);

	
	/**
	 * 构建库存菜单
	 */
	void CreateInventoryWidget(AMw_PlayerController_Base* MwPC, AMw_PlayerState_Base* MwPs,
						  UMw_AbilitySystemComponent* MwAsc, UMw_AttributeSet_Base* MwAs);
	/**
	 * 打开库存菜单
	 */
	void OpenInventoryMenu();

	/**
	 * 关闭库存菜单
	 */
	void CloseInventoryMenu();

};






/**
 *HUD 的职责划分
 *职责	说明
 *管理 Widget 实例	创建、缓存、显示/隐藏各个界面（单例模式，每个界面只有一个实例）
 *管理 WidgetController	创建并持有各个 Controller，确保数据与 UI 解耦
 *处理输入模式切换	打开菜单时切换到 GameAndUI，关闭时恢复 GameOnly
 *提供全局访问点	其他系统（如玩家角色）可通过 HUD 打开/关闭特定界面
 *监听全局事件	例如收到新物品时自动打开拾取提示等
 */