# Helicopter-Game
✨21 객체지향프로그래밍(2)_기말과제



## 👀개요

 "객체지향프로그래밍(2)"  수업의 기말과제 결과물이다.

  컴포넌트 기반 설계를 통하여 "헬리콥터 게임"과 게임의 맵을 만드는 "맵 에디터"를 만들었다.



## 1️⃣ Map Editor

  Map Editor의 기능은 다음과 같다.

1. 사용자가 마우스 클릭을 통해  블록을 생성하여 맵을 디자인 할 수 있다.

   ![](https://user-images.githubusercontent.com/63442636/147835479-19d44f8d-4bd4-477a-b686-b82596f68f49.gif)

2. 블록의 종류는 총 3개로, category의 화살표 버튼을 통해, 블록 종류를 변경 할 수 있다.

![](https://user-images.githubusercontent.com/63442636/147835510-db377280-91f8-4a67-ba6f-02a5856c0175.gif)

3. Clear 버튼으로 screen의 모든 블록을 지울 수 있다.
4. Load 버튼을 통해 이전에 저장된 맵을 불러올 수 있다.
5. Save 버튼을 통해 현재 맵을 새로운 이름으로 저장할 수 있다.(이름은 자동으로 123 번호를 매겨서 .txt 형식으로 저장된다.)



## 2️⃣ Helicopter Game

1. 횡스크롤 맵 이동

​       string 컨테이너를 이용하여, 맵 첫 열을 복사하여 마지막 열에 insert하도록 알고리즘을 구상하였다.

![](https://user-images.githubusercontent.com/63442636/147835581-2f46eddf-1a45-4650-8769-ce81e1c2085c.png)

2. Animation

AnimationClip이라는 구조체를 만들고, Vector 컨테이너를 활용하여, AnimationClip을 저장할 수 있도록 하였다.

```c++
struct AnimationClip {
	string		shape;
	Dimension	dim;
};
```

Animator을 Component 클래스를 상속받았아 작성하였고, 스크립트는 아래와 같다.

```c++
class Animator : public Component
{
	vector<AnimationClip> clips;//애니메이션 클립
	int currnetAnimation;//현재 진행중인 애니메이션 클립의 인덱스
protected:
	Renderer* renderer;
public:
	Animator(GameObject* gameObject) : Component(gameObject), currnetAnimation(0)
	{
		renderer = gameObject->getComponent<Renderer>();//랜더러 참조
	}

	void addClip(AnimationClip clip)//애니메이션 클립을 추가한다.
	{
		clips.push_back(clip);
	}

	void Play()
	{
		if (currnetAnimation == clips.capacity() - 1) currnetAnimation = 0;
        //마지막 클립이면 처음클립으로 돌아간다.
		else currnetAnimation++;


		renderer->setShape(clips[currnetAnimation].shape.c_str());
	}

	
};
```

💡 컴포넌트들은 Scene을 상속받은 클래스의 생성자에서 동적생성하여 GameObject에 넣어주었다.



3. Collision

![](https://user-images.githubusercontent.com/63442636/147835704-0b1b20ac-e93c-4e05-869c-93af35da8ec4.png)

모든 sprite들은 X*Y 사각형 형태로 이루어져있다. 충돌처리를 하기 위해서는 빈칸이 아닌 곳의 가장자리를 파악해야하기 때문에,

 "RigidBody" 컴포넌트를 새로 생성하여 다음과 같이 정의하였다.

```c++
  //Rigidbody 클래스의 멤버 벡터 컨테이너
  vector<edgePosition> rightedges;
	vector<edgePosition> leftedges;
	vector<edgePosition> upedges;
	vector<edgePosition> downedges;
```

```c++
//가장자리를 판단하는 알고리즘
for (int i = 0; i < dim.y; i++) {
	int rightcount = 0;//한 행당 왼,오 2개만 push_back해야함.
	int leftcount = 0;
	for (int j = 0; j < dim.x; j++) {
		if(i == 0 && sprite[j] != ' ')  upedges.push_back({ Direction::up,renderer->offset2Pos(j) });
		if(i == dim.y - 1 && sprite[i*dim.x+j] != ' ')  downedges.push_back({ Direction::down,renderer->offset2Pos(i * dim.x + j) });

		if (rightcount ==1 && leftcount ==1) continue;

		//left edge
		if (sprite[dim.x * i + j] != ' ' && leftcount == 0)
		{
			leftedges.push_back({ Direction::left,renderer->offset2Pos(dim.x * i + j) });
			leftcount++;
		}

		//right edge
		if (sprite[dim.x * i + dim.x - j - 1] != ' ' && rightcount == 0)
		{
			rightedges.push_back({ Direction::right,renderer->offset2Pos(dim.x * i + dim.x - j - 1) });
			rightcount++;
		}
	}
}
```

💡 RigidBody 컴포넌트 - Collider 컴포넌트 - Player 오브젝트와의 관계

![](https://user-images.githubusercontent.com/63442636/147835803-7b106ee2-931f-455d-8028-222d9106c751.png)

- RigidBody: 경계선 값을 계산하여 갖고 있음.(정보만 갖고 있다.)
- Collider: 리지드 바디의 값을 참조하여 플레이어에게 받은 방향과 위치 값을 토대로 충돌 여부를 판단한다.
- Player: Collider를 통해 움직임 가능성을 확인하고 그에 맞게 행동한다.



4.  Scene과 SceneManager

SceneManager과 Scene은 개별적인 관계로, SceneManager은 모든 Scene을 관리하기 때문에, 싱글톤 패턴으로 클래스를 설계하였다.

```c++
//SceneManager 멤버변수
int scenecount;// Vector 컨테이너안의 Scene개수 카운트
vector<Scene*> sceneinbuild;//모든 씬을 Vector에 주소를 참조하여 저장
static SceneManager* Instance;//싱글톤 패턴: 자기 자신을 전역변수로 참조값 갖고 있음
Scene* CurrentScene;//현재 씬
```

```c++
//Scene을 생성 할 때는 , Templete 함수를 활용하여 모든 Scene Class를 상속받은 Class들이 Upcasting되어 vector에 저장되게끔 만들었다.
template <typename T>
void createScene(T* newscene)
{
	sceneinbuild.push_back((Scene*)newscene);
}
```

[Video🎞](https://www.youtube.com/watch?v=vZtGq6ucDGI)

