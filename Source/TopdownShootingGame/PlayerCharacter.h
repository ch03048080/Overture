// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_DELEGATE(FSkillDelegate);

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOPDOWNSHOOTINGGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UWorld* World;

	// 타이머 시작 함수
	//UFUNCTION()
	void StartSkill1Timer();
	UFUNCTION(BlueprintCallable, Category = "Skill")
	void StartSkill2Timer();
private:
	// 타이머에서 호출되는 함수
	//UFUNCTION(BlueprintCallable, Category = "SkillDelegate") //델리게이트 함수에 UFUNCTION 안넣으면 크러쉬 뜸 
	//void Skill1Function(); //스킬 1 델리게이트에 바인딩 될 함수
	//UFUNCTION(BlueprintCallable, Category = "SkillDelegate")
	//void Skill2Function();
	
	//타이머 핸들러, 델리게이트 선언 
	//Skill 1 
	FTimerHandle TimerHandle;
	FTimerDelegate SkillDelegate;
	//Skill 2
	FTimerHandle TimerHandle2;
	FTimerDelegate SkillDelegate2;
	//Skill 3
	FTimerHandle TimerHandle3;
	FTimerDelegate SkillDelegate3;
	//적 스폰
	FTimerHandle EnemySpawnTimerHandle;
	FTimerDelegate EnemySpawnDelegate;
	//게임 플레이 타이머
	FTimerHandle GamePlayTimerHandle;
	FTimerDelegate GamePlayDelegate;

public:
	//데미지를 처리하고 체력을 업데이트하는 함수
	UFUNCTION(BlueprintCallable, Category = "CustomFunctions")
	void GetHurtAndUpdateHealth(float DamageAmount);

	//XP 관련 UI 업데이트 처리
	UFUNCTION(BlueprintCallable, Category = "Experience")
	void AddCoinExpericence(float PickupValue);
	UFUNCTION(BlueprintCallable, Category = "Experience")
	void StartSelectingSkills(); //스킬 레벨 업 UI 시작 시 
	UFUNCTION(BlueprintCallable, Category = "Experience")
	void ReturnToGame(); // 스킬 레벨 업 UI 종료 
	UFUNCTION(BlueprintCallable, Category = "Experience")
	void TopRightHUD_1(); // UI Update 함수
	UFUNCTION(BlueprintCallable, Category = "Experience")
	void TopRightHUD_2(); // UI Update 함수
	UFUNCTION(BlueprintCallable, Category = "Experience")
	void TopRightHUD_3(); // UI Update 함수
	UFUNCTION(BlueprintCallable, Category = "Experience")
	void TopRightHUD_4(); // UI Update 함수

	//스킬 출력 함수
	UFUNCTION(BlueprintCallable, Category = "Skill")//스킬 1 델리게이트에 바인딩할 함수
	void Skill_1();
	UFUNCTION(BlueprintCallable, Category = "Skill")//스킬 2 델리게이트에 바인딩할 함수
	void Skill_2();
	UFUNCTION(BlueprintCallable, Category = "Skill")//스킬 3 델리게이트에 바인딩할 함수
	void Skill_3();
	UFUNCTION(BlueprintCallable, Category = "Skill")//스킬 4 델리게이트에 바인딩할 함수
	void Skill_4();

	void SpawnSkill_1(int NumProjectile, float StartRotation, float RotIncrement); //SpellSpawnFireballs
	void SpawnSkill_2(int NumProjectile, float StartRotation, float RotIncrement); //SpellSpawnIceballs
	void InitializeSkill_3(int NumProjectile, float Rotation); //SpellSpawnlightballs
	
	//스킬 3 관련 선언들
	UClass* Skill3ActorClass;
	void DestroyAllActorsOfClass(UWorld* World, TSubclassOf<AActor> ActorClass);

	UFUNCTION(BlueprintCallable, Category = "Skill")
	void StartRotatingLight();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline") //스킬 액터를 회전 시키기 위한 타임라인 컴포넌트
	UTimelineComponent* SkillRotationTimeline;

	
	UPROPERTY(EditAnywhere, Category = "Skill")
	USceneComponent* Skill3PivotComponent;

	UPROPERTY(EditAnywhere, Category = "Skill")
	USceneComponent* Skill3SpawnComponent;

	UPROPERTY(EditAnywhere, Category = "Skill")
	FOnTimelineFloat ProgressFunction; //타임라인 
	
	UPROPERTY(EditAnywhere, Category = "Skill")
	FOnTimelineEvent TimelineFinishedEvent; //타임라인

	UPROPERTY(EditAnywhere, Category = "Timeline") //스킬 액터를 회전 시키기 위한 타임라인 커브
	UCurveFloat* RotationCurve;

	UFUNCTION(BlueprintCallable, Category = "Skill")//스킬 3 Start 함수
	void StartSkill_3();
	UFUNCTION(BlueprintCallable, Category = "Skill")
	void UpdateRotationProgress(float Value);
	UFUNCTION(BlueprintCallable, Category = "Skill")
	void OnRotationComplete();

	void SpawnSkill_4(); //SpellSpawnDarkballs

	
private:
	//카메라, 스프링 암 
	USpringArmComponent* CameraBoom;
	UCameraComponent* ViewCamera;

public:
	//위젯 클래스를 저장할 멤버 변수 선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> PlayerWidgetClass; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> DeathScreenWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> LevelingWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> TopRightHUDClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> StageClearWidgetClass;

	//위젯 인스턴스를 저장할 변수 선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Widget")
	UUserWidget* PlayerWidget; //WBP_Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* DeathScreenWidget; //WBP_DeathScreen
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* LevelingWidget; //WBP_Leveling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* TopRightHUDWidget; //WBP_TopRightHUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* StageClearWidget; //WBP_StageClearWidget

protected:	
	virtual void BeginPlay() override;
	
	// 향상된입력 - 캐릭터 이동 및 점프
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))	
		TObjectPtr<class UInputMappingContext> DefaultMappingContext; //늘리고싶으면 아래에 또하나 만들면됌. 	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))	
		TObjectPtr<class UInputAction> JumpAction; 	 //점프 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))	
		TObjectPtr<class UInputAction> MoveAction; 	//이동 액션
	void Move(const FInputActionValue& Value);	
	void Jump() override;
	

	//마우스 커서 방향으로 회전
	class APlayerController* CachedPlayerController = nullptr;
	FVector2D CachedMouseScreenPosition;
	void RotateMeshTowardsCursor();
	//void SetSphereMeshLocationUnderCursor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCapsuleComponent* PlayerCapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* CrosshairMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") //기본 스킬 피봇 생성
	USceneComponent* SkillPivot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") //스킬 피봇 생성
	USceneComponent* Skill3Pivot;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") //스킬 3 스폰 피봇 생성
	USceneComponent* RotatingSkillSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float PlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float PlayerMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float PlayerHealthPercentage;


	//캐릭터 XP 관련 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	float CurrentExperience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	float InPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	float ExpericenCap = 50.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	int CharacterLevel = 0;

public:
	//캐릭터 스킬 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	int SkillLevel_1 = 1; //SpellLevelFire

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	int SkillLevel_2 = 0; //SpellLevelIce

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	int SkillLevel_3 = 0; //SpellLevelLight

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	int SkillLevel_4 = 0; //SpellLevelDark

	//스킬 액터 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillActor")
	TSubclassOf<AActor> SpawnToSkill1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillActor")
	TSubclassOf<AActor> SpawnToSkill3;

	

private:
	//UPROPERTY(EditAnywhere, Category = "Rotaion")
	//FRotator PivotRotation;

	float DistanceToSpawnSkillActor;

public:

	//적 스폰 기능 구현
	//적 클래스 받아오기
	UClass* Enemy1_Dragon3;
	FString Dragon3ActorClassPath = "/Game/Blueprints/Enemies/BPMaster_Enemies.BPMaster_Enemies_C";

	UClass* Enemy2_BabyDragon;
	FString BabyDragonActorClassPath = "/Game/Blueprints/Enemies/BPMaster_Enemies_Child_Enemy2_Baby.BPMaster_Enemies_Child_Enemy2_Baby_C";

	UClass* Enemy3_GoldDragon;
	FString GoldDragonActorClassPath = "/Game/Blueprints/Enemies/BPMaster_Enemies_Child_Enemy3_GoldDragon.BPMaster_Enemies_Child_Enemy3_GoldDragon_C";

	UClass* Enemy4_MaxDragon3;
	FString MaxDragon3ActorClassPath = "/Game/Blueprints/Enemies/BPMaster_Enemies_Child_Enemy4_MaxDragon.BPMaster_Enemies_Child_Enemy4_MaxDragon_C";
	ACharacter* SpawnedEnemy; // 스폰된 Enemy 저장

	UFUNCTION(BlueprintCallable, Category = "SpawnEnemyTimeline")
	void SpawnEnemy(); 
	void StartSpawnEnemy();
	float SpawnInterval = 0.0f;
	float SpawnIntervalDecreaseRate = 0.0f;
	float MinSpawnInterval = 0.0f;
	///FVector SpawnLocation, FRotator SpawnRotation
	void SelectRandomSpawnLocation();
	FVector SpawnLocation;
	FRotator SpawnRotation;


//게임 플레이 타이머 기능
	float TimerDuration = 100.0f;
	float CurrentTime = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "GamePlayTimer")
	void UpdateTimer();
	void OnTimerEnd();

	//타이머 해제 함수
	UFUNCTION(BlueprintCallable, Category = "ResetTimer")
	void ResetTimer();

	//플레이어 스코어 계산 함수
	int PlayerScore = 0;
	void CalculatePlayerScore();

	//플레이어 체력 회복 함수 (체력 회복 물약 먹었을 때)
	UFUNCTION(BlueprintCallable, Category = "Item")
	void PlayerHealthRecovery();
};
