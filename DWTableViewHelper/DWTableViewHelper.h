//
//  DWTableViewHelper.h
//  DWTableViewHelper
//
//  Created by Wicky on 2017/1/13.
//  Copyright © 2017年 Wicky. All rights reserved.
//

/**
 DWTableViewHelper
 TableView工具类
 抽出TableView代理，减小VC压力，添加常用代理映射
 
 version 1.0.0
 添加常用代理映射
 添加helper基础属性
 
 version 1.0.1
 去除注册，改为更适用的重用模式
 
 version 1.0.2
 添加多分组模式
 
 version 1.0.3
 添加选择模式及相关api
 
 version 1.0.4
 添加helper设置cell类型及复用标识
 
 version 1.0.5
 将cell的基础属性提出协议，helper与model同时遵守协议
 
 version 1.0.6
 修正占位视图展示时机，提供两个刷新列表扩展方法，提供展示、隐藏占位图接口
 
 version 1.0.7
 添加选则模式下单选多选控制
 
 version 1.0.8
 补充组头视图、尾视图行高代理映射并简化代理链
 
 version 1.0.9
 cell基类添加父类实现强制调用宏、断言中给出未能加载的cell类名
 
 version 1.1.0
 改变cell划线机制，改为系统分割线，添加分割线归0方法
 添加自动行高计算并缓存
 cell添加xib支持
 修复选择模式选中后关闭再次开启选择同一个无法选中bug
 更换去除选择背景方式，解决与选择模式的冲突
 映射所有代理
 
 version 1.1.1
 添加自适应模式最小行高限制及最大行高设置
 添加数据源的容错机制，但这并不是你故意写错的理由=。=
 添加屏幕判断，当位置方向时，默认返回竖屏
 额外补充动画代理、支持CAAnimation及DWAnimation
 
 version 1.1.2
 展示动画逻辑修改，DWAnimation动画展示方法替换
 
 version 1.1.3
 滚动优化模式添加
 高速忽略模式完成
 懒加载模式完成
 懒加载模式动画隐藏，更加平滑，修复刷新bug。
 有没有美工妹子给切几张占位图。。我做的图太丑了。。
 
 version 1.1.4
 添加占位图代理
 cell选择样式逻辑修改
 反选模式算法优化
 添加以数组形式选择方法
 添加返回两坐标间所有有效坐标方法
 添加选择模式下行为代理
 去除DWTableViewHelperCell中-setupConstraints:的强制父类实现调用
 高速滚动截图优化模式完成
 懒加载优化模式setOffset加载逻辑补充
 
 version 1.1.5
 添加版本判断
 helper添加自动适配TableView内距API
 适配iOS11后tableView的sectionHeader与footer代理高度问题
 
 version 1.1.6
 修改自动计算高度API中忽略cell辅助视图宽度的bug
 修复自动代理中heightForHeader代理映射错误bug
 添加iOS 11后refreshControl自动修复API
 更新事务类相关API
 
 version 1.1.7
 添加头视图自动放大
 cell添加计算行高标志位
 
 version 1.1.7.1
 model添加重新自动计算高度接口
 helper添加设置所有model均需重新计算接口
 
 version 1.1.7.2
 当无指定行高时，添加使用tableView.rowHeight逻辑
 
 version 1.1.7.3
 添加外部自行实现cellForRow代理后，取重用cell的方法及处理LoadDataMode的方法
 
 version 1.1.7.4
 移除LoadDataMode方法，内部自动调用，开发者无需处理

 version 1.1.7.5
 修复reload前判断是否存在数据引起的处理错误
 
 version 1.1.7.6
 跟随FDTemplateLayoutCell补充自动计算行高的核心算法（本次发现在计算行高时，若遇到行高计算不准确时（确保约束正确的情况下通常是因为label为多行Label且Label的宽度不定，可能横向约束存在MoreThanOrEqualTo或者LessThanOrEqualTo此类约束导致无法准去自动计算行高），可以通过设置Label的label.preferredMaxLayoutWidth来尝试解决问题，截至目前我亲测好用）
 修改DWTableViewHelperModel中cellID及cellClassStr的默认值行为。当设置cellClassStr时自动更改cellID默认值，给与不设cellID而程序正常运行更大的灵活性
 修改部分代理当外部返回不合法值时，按照内部既定逻辑处理。为外部单独定制个别cell而其他cell使用默认行为提供可能性
 增加对单独cell的自动行高控制
 增加对cell动作的严格模式
 增加model对当前展示cell及indexPath的引用
 

 */

#import <UIKit/UIKit.h>

#pragma mark --- tableView 代理映射 ---
@class DWTableViewHelperCell;
@protocol DWTableViewHelperDelegate <NSObject>

@optional

///展示定制
-(void)dw_tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath;
-(void)dw_tableView:(UITableView *)tableView willDisplayHeaderView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
-(void)dw_tableView:(UITableView *)tableView willDisplayFooterView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
-(void)dw_tableView:(UITableView *)tableView didEndDisplayingCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath*)indexPath NS_AVAILABLE_IOS(6_0);
-(void)dw_tableView:(UITableView *)tableView didEndDisplayingHeaderView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
-(void)dw_tableView:(UITableView *)tableView didEndDisplayingFooterView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);

///高度定制
-(CGFloat)dw_tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
-(CGFloat)dw_tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section;
-(CGFloat)dw_tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section;

///组头、组尾视图
-(UIView *)dw_tableView:(__kindof UITableView *)tableView viewForHeaderInSection:(NSInteger)section;
-(UIView *)dw_tableView:(__kindof UITableView *)tableView viewForFooterInSection:(NSInteger)section;

///辅助视图
-(void)dw_tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath;

///选中高亮
-(BOOL)dw_tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath;
-(void)dw_tableView:(UITableView *)tableView didHighlightRowAtIndexPath:(NSIndexPath *)indexPath;
-(void)dw_tableView:(UITableView *)tableView didUnhighlightRowAtIndexPath:(NSIndexPath *)indexPath;

///选中
-(NSIndexPath *)dw_tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath;
-(NSIndexPath *)dw_tableView:(UITableView *)tableView willDeselectRowAtIndexPath:(NSIndexPath *)indexPath;
-(void)dw_tableView:(__kindof UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
-(void)dw_tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(NSIndexPath *)indexPath;

///编辑
-(UITableViewCellEditingStyle)dw_tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath;
-(NSString *)dw_tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath;
-(NSArray<UITableViewRowAction *> *)dw_tableView:(UITableView *)tableView editActionsForRowAtIndexPath:(NSIndexPath *)indexPath;
-(UISwipeActionsConfiguration *)dw_tableView:(UITableView *)tableView leadingSwipeActionsConfigurationForRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);
-(UISwipeActionsConfiguration *)dw_tableView:(UITableView *)tableView trailingSwipeActionsConfigurationForRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);
-(BOOL)dw_tableView:(UITableView *)tableView shouldIndentWhileEditingRowAtIndexPath:(NSIndexPath *)indexPath;///grouped 模式下有效，返回移动时是否缩进
-(void)dw_tableView:(UITableView *)tableView willBeginEditingRowAtIndexPath:(NSIndexPath *)indexPath;
-(void)dw_tableView:(UITableView *)tableView didEndEditingRowAtIndexPath:(NSIndexPath *)indexPath;
-(NSIndexPath *)dw_tableView:(UITableView *)tableView targetIndexPathForMoveFromRowAtIndexPath:(NSIndexPath *)sourceIndexPath toProposedIndexPath:(NSIndexPath *)proposedDestinationIndexPath;///移动时可通过源位置和目标位置判断应该到达的位置，通常情况下无需实现或返回proposedDestinationIndexPath即为不做特殊处理
-(BOOL)dw_tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath;
-(BOOL)dw_tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath;

///缩进
-(NSInteger)dw_tableView:(UITableView *)tableView indentationLevelForRowAtIndexPath:(NSIndexPath *)indexPath;///返回cell缩进级别。cell缩进级别不同时可调用此代理

///Copy/Paste 长按显示菜单栏，三个代理需同时实现
-(BOOL)dw_tableView:(UITableView *)tableView shouldShowMenuForRowAtIndexPath:(NSIndexPath *)indexPath;
-(BOOL)dw_tableView:(UITableView *)tableView canPerformAction:(SEL)action forRowAtIndexPath:(NSIndexPath *)indexPath withSender:(id)sender;
-(void)dw_tableView:(UITableView *)tableView performAction:(SEL)action forRowAtIndexPath:(NSIndexPath *)indexPath withSender:(id)sender;

///焦点 控制焦点的移动，可用于遥控器相关开发
-(BOOL)dw_tableView:(UITableView *)tableView canFocusRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
-(BOOL)dw_tableView:(UITableView *)tableView shouldUpdateFocusInContext:(UITableViewFocusUpdateContext *)context NS_AVAILABLE_IOS(9_0);
-(void)dw_tableView:(UITableView *)tableView didUpdateFocusInContext:(UITableViewFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator NS_AVAILABLE_IOS(9_0);
-(NSIndexPath *)dw_indexPathForPreferredFocusedViewInTableView:(UITableView *)tableView NS_AVAILABLE_IOS(9_0);
-(BOOL)dw_tableView:(UITableView *)tableView shouldSpringLoadRowAtIndexPath:(NSIndexPath *)indexPath withContext:(id<UISpringLoadedInteractionContext>)context API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);
-(BOOL)dw_tableView:(UITableView *)tableView shouldBeginMultipleSelectionInteractionAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);
-(void)dw_tableView:(UITableView *)tableView didBeginMultipleSelectionInteractionAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);
-(void)dw_tableViewDidEndMultipleSelectionInteraction:(UITableView *)tableView API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);
-(UIContextMenuConfiguration *)dw_tableView:(UITableView *)tableView contextMenuConfigurationForRowAtIndexPath:(NSIndexPath *)indexPath point:(CGPoint)point API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);
-(UITargetedPreview *)dw_tableView:(UITableView *)tableView previewForHighlightingContextMenuWithConfiguration:(UIContextMenuConfiguration *)configuration API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);
-(UITargetedPreview *)dw_tableView:(UITableView *)tableView previewForDismissingContextMenuWithConfiguration:(UIContextMenuConfiguration *)configuration API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);
-(void)dw_tableView:(UITableView *)tableView willPerformPreviewActionForMenuWithConfiguration:(UIContextMenuConfiguration *)configuration animator:(id<UIContextMenuInteractionCommitAnimating>)animator API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

///数据源
-(NSInteger)dw_tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section;
-(DWTableViewHelperCell *)dw_tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
-(NSInteger)dw_numberOfSectionsInTableView:(UITableView *)tableView;
-(NSString *)dw_tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section;
-(NSString *)dw_tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section;
-(NSArray<NSString *> *)dw_sectionIndexTitlesForTableView:(UITableView *)tableView;
-(NSInteger)dw_tableView:(UITableView *)tableView sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)index;
-(void)dw_tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath;
-(void)dw_tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath;

///预加载
-(void)dw_tableView:(UITableView *)tableView prefetchRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
-(void)dw_tableView:(UITableView *)tableView cancelPrefetchingForRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;

///滑动
-(void)dw_scrollViewDidScroll:(UIScrollView *)scrollView;
-(void)dw_scrollViewDidZoom:(UIScrollView *)scrollView;
-(void)dw_scrollViewWillBeginDragging:(UIScrollView *)scrollView;
-(void)dw_scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset;
-(void)dw_scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;
-(void)dw_scrollViewWillBeginDecelerating:(UIScrollView *)scrollView;
-(void)dw_scrollViewDidEndDecelerating:(UIScrollView *)scrollView;
-(void)dw_scrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView;
-(UIView *)dw_viewForZoomingInScrollView:(UIScrollView *)scrollView;
-(void)dw_scrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(UIView *)view;
-(void)dw_scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(CGFloat)scale;
-(BOOL)dw_scrollViewShouldScrollToTop:(UIScrollView *)scrollView;
-(void)dw_scrollViewDidScrollToTop:(UIScrollView *)scrollView;
-(void)dw_scrollViewDidChangeAdjustedContentInset:(UIScrollView *)scrollView API_AVAILABLE(ios(11.0), tvos(11.0));

#pragma mark --- Additional Helper Delegate ---
///动画 支持返回CAAniamion对象、DWAnimation对象
-(BOOL)dw_tableView:(UITableView *)tableView shouldAnimationWithCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath;
-(id)dw_tableView:(UITableView *)tableView showAnimationWithCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath;

///cell占位图（仅优化模式下有效）
-(UIImage *)dw_tableView:(UITableView *)tableView loadDataPlaceHolderForCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath;

///选择（仅选择模式下有效）
///若代理返回YES，则选择行为由代理控制
/**
 选择（仅选择模式下有效）
 
 注：
 若代理返回YES，则选择行为由代理控制
 否则由系统控制选择行为
 
 切记，因为无论返回YES还是NO代理都会执行，故所有返回NO情况均应先于YES情况执行return语句。
 */
-(BOOL)dw_tableView:(UITableView *)tableView selectModeWillSelectRowAtIndexPath:(NSIndexPath *)indexPath;
-(BOOL)dw_tableView:(UITableView *)tableView selectModeWillDeselectRowAtIndexPath:(NSIndexPath *)indexPath;

@end

#pragma mark --- cell 基础属性协议---
@protocol DWTableViewHelperCellProperty <NSObject>
/**
 通过helper设置为批量设置，优先级较低；通过model设置为特殊设置，优先级较高。
 可通过helper批量设置后针对特殊cell通过model单独设置属性。
 */

///cell类型与复用标识
/**
 优先级：映射代理 > 数据模型 > helper
 
 cell类型与复用标识两者必须同时在helper或model中至少设置一次。
 若helper及model中均设置正确则model中优先级更高
 
 通过helper设置cell类型与复用标识更加适用于以下场景：
 需要共享数据模型但是要展示不同种类cell的场景
 
 此时需要手动将model中cell类型或者复用标识置为nil（理论上两者均存在默认值所以需要置nil）并通过helper进行指定cell类型
 */
///cell类型
@property (nonatomic ,copy) NSString * cellClassStr;

///复用标识
@property (nonatomic ,copy) NSString * cellID;

///是否使用自使用行高
/**
 优先级最低，计算一次并缓存
 */
@property (nonatomic ,assign) BOOL useAutoRowHeight;

///helper行高
/**
 优先级：映射代理行高 > 数据模型行高 > helper行高 > 默认行高44
 */
@property (nonatomic ,assign) CGFloat cellRowHeight;

///选中模式图标
/**
 优先级：数据模型图片 > helper图片 > 系统默认图标
 
 若设置helper图片后，model设置图片不受影响，未设置图片的model将会被设置为helper图片。
 若通过helper批量设置后，个别cell要使用系统默认图标，请将对应model的图片设置为nil。
 */
///选择模式选中图标
@property (nonatomic ,strong) UIImage * cellEditSelectedIcon;

///选择模式未选中图标
@property (nonatomic ,strong) UIImage * cellEditUnselectedIcon;

@end

typedef NS_ENUM(NSUInteger, DWTableViewHelperLoadDataMode) {///数据加载优化模式
    DWTableViewHelperLoadDataDefaultMode,///无优化
    DWTableViewHelperLoadDataLazyMode,///滚动中不加载cell
    DWTableViewHelperLoadDataIgnoreHighSpeedMode,///不加载高速滚出的cell
    DWTableViewHelperLoadDataIgnoreHighSpeedWithSnapMode,///高速滚出的cell加载截图
};

#pragma mark --- DWTableViewHelper 工具类 ---
@class DWTableViewHelperModel;
/**
 Helper工具类
 */
@interface DWTableViewHelper : NSObject<DWTableViewHelperCellProperty>

///代理
@property (nonatomic ,weak) id<DWTableViewHelperDelegate> helperDelegate;

///数据源
@property (nonatomic ,strong) NSArray * dataSource;

///无数据占位图
@property (nonatomic ,strong) UIView * placeHolderView;

///多分组模式
@property (nonatomic ,assign) BOOL multiSection;

///设置是否为选择模式
@property (nonatomic ,assign) BOOL selectEnable;

///是否允许多选
@property (nonatomic ,assign) BOOL multiSelect;

///返回被选中的cell的indexPath的数组
@property (nonatomic ,strong) NSArray * selectedRows;

///最小自动行高
@property (nonatomic ,assign) CGFloat minAutoRowHeight;

///最大自动行高
@property (nonatomic ,assign) CGFloat maxAutoRowHeight;

///cell展示动画
@property (nonatomic ,strong) id cellShowAnimation;


/**
 数据加载模式
 
 此属性为优化tableView滚动时流畅性的属性
 
 DWTableViewHelperLoadDataDefaultMode
 默认模式
 不含优化体验效果。默认在每个cell即将出现时进行绘制。
 
 DWTableViewHelperLoadDataLazyMode
 懒加载模式
 当tableView滚动时，认为当前cell不需要加载，以占位图进行展示
 
 DWTableViewHelperLoadDataIgnoreHighSpeedMode
 高速滚动忽略模式
 当tableView快速滚动时，则认为当中快速略过的cell不需加载，以占位图进行展示
 
 DWTableViewHelperLoadDataIgnoreHighSpeedWithSnapMode
 高速滚动加载截图模式
 当tableView快速滚动时，则认为当中快速略过的cell不需展示真实数据，以缓存的对应cell截图进行显示，若为缓存过截图则以占位图展示。（截图会在tableView停止滚动后提交截图任务，截图任务会在runLoop进入空闲状态时自动执行）
 
 注：
 1.高速忽略模式下，由于需要计算结束滚动处所要展示的cell，故适用于定行高时，若在自动计算行高模式下会有偏差，且偏差具有累积效应。
 2.使用DWTableViewHelperLoadDataIgnoreHighSpeedMode模式时，若cell需要自行实现-(UIView *)hitTest:withEvent:方法，为了更好的滑动体验，请调用父类实现。
 */
@property (nonatomic ,assign) DWTableViewHelperLoadDataMode loadDataMode;

/**
 优化模式下，不加载的cell展示的图片
 
 注：
 优先级：代理图片 > helper图片 > 默认图标
 */
@property (nonatomic ,strong) UIImage * loadDataPlaceHolder;

///忽略模式下当快速滚动级别（数字越小，占位cell越多）
@property (nonatomic ,assign) NSUInteger ignoreCount;

/**
 严格控制cell动作代理
 
 当行高大于44时，tableView首次会按照行高44计算执行wilDisplayCell及cellForRow两个代理，即实际展示的cell要比代理展示的cell较少。可以通过对外屏蔽此处代理调用来保证只有cell即将被展示出时才会调用willDisplayCell及cellForRow两个代理。默认关闭。
 */
@property (nonatomic ,assign) BOOL strictCellAction;

///实例化方法
-(instancetype)initWithTabV:(__kindof UITableView *)tabV dataSource:(NSArray *)dataSource;

///取出对应indexPath对应的数据模型（具有容错机制）
-(__kindof DWTableViewHelperModel *)modelFromIndexPath:(NSIndexPath *)indexPath;

///根据重用id及indexPath取出重用的cell（外界重写cellForRow代理时调用，可根据模型动态生成cell）
-(__kindof DWTableViewHelperCell *)dequeueReusableCellWithModel:(__kindof DWTableViewHelperModel *)model;

///让分割线归零
-(void)setTheSeperatorToZero;

///刷新列表同时自动处理占位图
-(void)reloadDataAndHandlePlaceHolderView;

///刷新列表并在完成时进行回调
-(void)reloadDataWithCompletion:(dispatch_block_t)completion;

///展示占位图
-(void)showPlaceHolderView;

///隐藏占位图
-(void)hidePlaceHolderView;

///设置全部选中或取消全部选中
-(void)setAllSelect:(BOOL)select;

///设置指定分组全部选中或取消全部选中
-(void)setSection:(NSUInteger)section allSelect:(BOOL)select;

///设置集合内的坐标的选择状态
-(void)setSelect:(BOOL)select indexPaths:(NSArray <NSIndexPath *>*)indexPaths;

/**
 返回两个坐标之间所有有效坐标的数组

 @param idxPA 较小的坐标
 @param idxPB 较大的坐标

 @return 包含两者的所有有效坐标的数组
 */
-(NSArray <NSIndexPath *> *)indexPathsBetween:(NSIndexPath *)idxPA and:(NSIndexPath *)idxPB;

///反选指定分组
-(void)invertSelectSection:(NSUInteger)section;

///反选全部
-(void)invertSelectAll;

///激活tableView的自动调整状态（适配iOS11）
-(void)enableTableViewContentInsetAutoAdjust:(BOOL)autoAdjust inViewController:(UIViewController *)vc;

///修复iOS11后refreshControl位置错误
-(void)fixRefreshControlInsets;

/**
 设置自动放大的头视图，与tableHeaderView相互冲突

 @param header 设置的headerView
 @param handler 当滚动时的触发回调，可在此处处理导航透明度
 */
-(void)setAutoZoomHeader:(UIView *)header scrollHandler:(void(^)(CGFloat contentoffset))handler;

///设置当前所有模型均为需要重新自动计算高度
-(void)setAllNeedsReAutoCalculateRowHeight;

@end

#pragma mark --- DWTableViewHelperModel 数据模型基类 ---
/**
 基础Model类
 
 数据模型请继承自本类
 本类所有属性、方法均为统一接口，子类可重写方法，注意调用父类实现
 */
@interface DWTableViewHelperModel : NSObject<DWTableViewHelperCellProperty>

///自动计算的行高
/**
 会根据横竖屏进行切换
 */
@property (nonatomic ,assign) CGFloat autoCalRowHeight;

///是否从xib文件中加载cell，默认为NO
@property (nonatomic ,assign) BOOL loadCellFromNib;

///配合DWTableViewHelperLoadDataIgnoreHighSpeedMode使用，标志cell是否被绘制过
@property (nonatomic ,assign ,readonly) BOOL cellHasBeenDrawn;

/**
 当前正在展示的cell
 
 在willDisplayCell之后被赋值为对应的cell，在didEndDisplaying之后被置空
 */
@property (nonatomic ,weak ,readonly) __kindof DWTableViewHelperCell * currentDisplayCell;

/**
 当前正在展示的cell对应的indexPath
 
 在willDisplayCell之后被赋值为对应的cell的indexPath，在didEndDisplaying之后被置空
 */
@property (nonatomic ,strong ,readonly) NSIndexPath * currentDisplayIndexPath;



///设置需要重新自动计算高度
-(void)setNeedsReAutoCalculateRowHeight;

@end

#pragma mark --- DWTableViewHelperCell cell基类 ---
/**
 基础Cell类
 
 Cell请继承自本类
 本类所有属性、方法均为统一接口，子类可重写方法，注意调用父类实现
 */

extern NSNotificationName const DWTableViewHelperCellHitTestNotification;

@interface DWTableViewHelperCell : UITableViewCell

///计算用cell，只有仅用于自动计算行高的cell会将此标志位置为真
@property (nonatomic ,assign ,readonly) BOOL just4Cal;

///数据模型
@property (nonatomic ,strong)__kindof DWTableViewHelperModel * model;

///设置子视图
-(void)setupUI NS_REQUIRES_SUPER;

///设置子视图约束
-(void)setupConstraints;

///设置数据模型
-(void)setModel:(__kindof DWTableViewHelperModel *)model NS_REQUIRES_SUPER;


/**
 展示加载数据视图

 @param image 加载数据图片
 
 在优化滚动模式下系统会自行调用。会以当前cell大小展示指定的图片。
 开发者也可调用或重写此方法，必须实现父类方法
 */
-(void)showLoadDataPlaceHolder:(UIImage *)image height:(CGFloat)height NS_REQUIRES_SUPER;

/**
 隐藏加载数据视图
 
 在优化滚动模式下系统会自行调用。隐藏视图。
 开发者也可调用或重写此方法，必须实现父类方法
 */
-(void)hideLoadDataPlaceHolerAnimated:(BOOL)animated NS_REQUIRES_SUPER;

///hit test（一般情况下无需自行实现，如需自行实现，必须调用父类实现）
-(UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event NS_REQUIRES_SUPER;
@end
