#include "yaTitleScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaPlayerScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaSpriteRenderer.h"
#include "yaGridScript.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaCollider2D.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaAnimator.h"
#include "yaLight.h"
#include "yaPaintShader.h"
#include "yaParticleSystem.h"

namespace ya
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Tilte)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{
		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		cameraObj->SetName(L"MainCamera");
		cameraObj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -20.0f));
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		{
			GameObject* player = object::Instantiate<GameObject>(eLayerType::Player);
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
			player->GetComponent<Transform>()->SetScale(Vector3(5.0f, 5.0f, 5.0f));
			//player->GetComponent<Transform>()->SetRotation(Vector3(15.0f, 45.0f, 0.0f));
			player->SetName(L"Player");
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMaterial(Resources::Find<Material>(L"BasicMaterial"));
			mr->SetMesh(Resources::Find<Mesh>(L"CubeMesh"));
			player->AddComponent<PlayerScript>();
		}

		{
			GameObject* player = object::Instantiate<GameObject>(eLayerType::Player);
			player->GetComponent<Transform>()->SetPosition(Vector3(-15.0f, 0.0f, 10.0f));
			player->GetComponent<Transform>()->SetScale(Vector3(5.0f, 5.0f, 5.0f));
			//player->GetComponent<Transform>()->SetRotation(Vector3(15.0f, 45.0f, 0.0f));
			player->SetName(L"Player");
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMaterial(Resources::Find<Material>(L"DefferdMaterial"));
			mr->SetMesh(Resources::Find<Mesh>(L"CubeMesh"));
			player->AddComponent<PlayerScript>();
		}

		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->SetName(L"directionalLight");

			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 100.0f, 0.0f));
			directionalLight->GetComponent<Transform>()->SetRotation(Vector3(45.0f, 0.0f, 0.0f));

			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 1.0f, 1.0f));
			lightComp->SetSpecular(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			lightComp->SetAmbient(Vector4(0.15f, 0.15f, 0.15f, 1.0f));
		}

		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}

		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}
