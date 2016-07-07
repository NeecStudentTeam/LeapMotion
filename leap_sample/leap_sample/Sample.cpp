/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#include <iostream>
#include <cstring>
#include "Leap.h"

using namespace Leap;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

  private:
};

//指の名前
const std::string fingerNames[] = {"親指", "人差し指", "中指", "薬指", "小指"};
//指骨の名前
const std::string boneNames[] = {"中手骨", "基節骨", "中節骨", "末節骨"};
//ジェスチャーの認識状態
const std::string stateNames[] = {"認識なし", "開始", "更新", "終了"};

//リスナーの初期化処理　リスナーを追加した時に呼び出される
void SampleListener::onInit(const Controller& controller) {
  std::cout << "ジェスチャーを取得します。" << std::endl;
}

//LeapMotionセンサーと接続されたときに呼び出される
void SampleListener::onConnect(const Controller& controller) {
  std::cout << "LeapMotionと接続されました。" << std::endl;

  //ジェスチャーの登録
  //サークル
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  //スワイプ
  //controller.enableGesture(Gesture::TYPE_SWIPE);
  //キータップ
  //controller.enableGesture(Gesture::TYPE_KEY_TAP);
  //スクリーンタップ
  //controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  
}

//LeapMotionセンサーから切断されたとき呼び出される
void SampleListener::onDisconnect(const Controller& controller) {
  std::cout << "LeapMotionと切断されました。" << std::endl;
}

//リスナーの終了処理　リスナーを削除した時に呼び出される
void SampleListener::onExit(const Controller& controller) {
  std::cout << "終了" << std::endl;
}

//フレームのデータが更新された時に呼び出される
//モーションセンサーのデータはすべてここで処理される
void SampleListener::onFrame(const Controller& controller) {
  
  const Frame frame = controller.frame();
  
  /*std::cout << "フレームID: " << frame.id()
            << ", 認識している手の数: " << frame.hands().count()
            << ", 認識している指の数: " << frame.fingers().extended().count()
            << ", 認識しているツールの数: " << frame.tools().count()
            << ", 認識しているジェスチャーの数: " << frame.gestures().count() << std::endl;*/

  //std::cout << "フレーム数;" << frame.currentFramesPerSecond() << std::endl;


  HandList hands = frame.hands();
  for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
    
	// 手の取得
    const Hand hand = *hl;
    std::string handType = hand.isLeft() ? "左手" : "右手";
   
	//取得している手の情報
	/*std::cout << std::string(2, ' ') << handType << ", 手のID: " << hand.id()
              << ", 手の座標: " << hand.palmPosition() << std::endl;*/
    
	/*------指、手の丸みから表せる球の計算する----------
    //const Vector normal = hand.palmNormal();
    //const Vector direction = hand.direction();

    // 手の傾き,開き,角度から計算する
    
	/*std::cout << std::string(2, ' ') <<  "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
              << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
              << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;*/
	
	//---------------------------------------------------

    // 腕の取得
    /*Arm arm = hand.arm();
	std::cout << std::string(2, ' ') <<  "手の方向: " << arm.direction()
              << " 手首の座標: " << arm.wristPosition()
              << "  肘の座標" << arm.elbowPosition() << std::endl;*/

    // 指の取得
    const FingerList fingers = hand.fingers();
    for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
      const Finger finger = *fl;
      
	  /*std::cout << std::string(4, ' ') <<  fingerNames[finger.type()]
                << " , 指のID: " << finger.id()
                << ", 長さ: " << finger.length()
                << "mm, 幅: " << finger.width() << std::endl;*/

      // 指骨の取得
      for (int b = 0; b < 4; ++b) {
        Bone::Type boneType = static_cast<Bone::Type>(b);
        Bone bone = finger.bone(boneType);
        
		/*std::cout << std::string(6, ' ') <<  boneNames[boneType]
                  << " , start: " << bone.prevJoint()
                  << ", end: " << bone.nextJoint()
                  << ", 方向: " << bone.direction() << std::endl;*/
      }
    }
  }

  // ツールの取得
  /*const ToolList tools = frame.tools();
  for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
    const Tool tool = *tl;
    std::cout << std::string(2, ' ') <<  "Tool, id: " << tool.id()
              << ", 座標: " << tool.tipPosition()
              << ", 方向: " << tool.direction() << std::endl;
  }*/

  // ジェスチャーの取得
  const GestureList gestures = frame.gestures();
  for (int g = 0; g < gestures.count(); ++g) {
    Gesture gesture = gestures[g];


    switch (gesture.type()) {
	  
	  //サークル
      case Gesture::TYPE_CIRCLE:
      {
        CircleGesture circle = gesture;
        std::string clockwiseness;


		//サークルの方向
        if (circle.pointable().direction().angleTo(circle.normal()) <= PI/2) {
          clockwiseness = "時計周り";
        } else {
          clockwiseness = "反時計周り";
        }

        // 角度の計算
        float sweptAngle = 0;
        if (circle.state() != Gesture::STATE_START) {
          CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
          sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
        }
        
		
		std::cout << std::string(2, ' ')
                  << "サークルID: " << gesture.id()
                  << ", ジェスチャーの状態: " << stateNames[gesture.state()]
                  << ", サークルの進行状況: " << circle.progress()
                  << ", 半径: " << circle.radius()
                  << ", 角度 " << sweptAngle * RAD_TO_DEG
                  <<  ", " << clockwiseness << std::endl;

        break;
      }

	  //スワイプ
      case Gesture::TYPE_SWIPE:
      {
        SwipeGesture swipe = gesture;
        std::cout << std::string(2, ' ')
          << "ジェスチャーID: " << gesture.id()
          << ", ジェスチャーの状態: " << stateNames[gesture.state()]
          << ", 方向: " << swipe.direction()
          << ", 速度: " << swipe.speed() << std::endl;
        break;
      }

	  //キータップ
      /*case Gesture::TYPE_KEY_TAP:
      {
        KeyTapGesture tap = gesture;
        std::cout << std::string(2, ' ')
          << "ジェスチャーID: " << gesture.id()
          << ", ジェスチャーの状態: " << stateNames[gesture.state()]
          << ", 検出位置: " << tap.position()
          << ", 方向: " << tap.direction()<< std::endl;
        break;
      }*/
	  


	  //スクリーンタップ
      /*case Gesture::TYPE_SCREEN_TAP:
      {
        ScreenTapGesture screentap = gesture;
        std::cout << std::string(2, ' ')
          << "ジェスチャーID: " << gesture.id()
          << ", ジェスチャーの状態: " << stateNames[gesture.state()]
          << ", 検出位置: " << screentap.position()
          << ", 方向: " << screentap.direction()<< std::endl;
        break;
      }*/

	  //認識してないジェスチャー
	  default:
        std::cout << std::string(2, ' ')  << "認識されてないジェスチャーです。" << std::endl;
        break;
    }
  }

  /*if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
    std::cout << std::endl;
  }*/

}

//アプリケーションがアクティブになった時に呼び出される
void SampleListener::onFocusGained(const Controller& controller) {
  std::cout << "アプリケーションがアクティブになりました。" << std::endl;
}

//アプリケーションがアクティブでなくなった時に呼び出される
void SampleListener::onFocusLost(const Controller& controller) {
  std::cout << "アプリケーションがアクティブではなくなりました。" << std::endl;
}

//LeapMotionコントローラーの接続/切断された時に呼び出される
void SampleListener::onDeviceChange(const Controller& controller) {
  std::cout << "LeapMotionと切断されました" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "LeapMotionID: " << devices[i].toString() << std::endl;
    std::cout << "  データ配信状態: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

//LeapMotionのデータを取得しているWindowsサービスと接続された時に呼び出される
void SampleListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected:Windowsサービスと接続されました。" << std::endl;
}

//LeapMotionのデータを取得しているWindowsサービスと切断された時に呼び出される
void SampleListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected:Windowsサービスと切断されました。" << std::endl;
}


//leapmotionメインプログラム
int main(int argc, char** argv) {
  // リスナーの作成
  SampleListener listener;
  Controller controller;

  // イベントを受けとるリスナーを登録
  controller.addListener(listener);

  //起動時に引数に"--bg"が設定されていた場合バクグラウンドモードで動作させる
  //ほとんどの場合バックグラウンドモードで動作する事になるため解説時以外ではif文をコメントアウトする
  if (argc > 1 && strcmp(argv[1], "--bg") == 0)
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  // Enterキーが押されるまで処理を続ける
  std::cout << "終了する場合はEnterを押してください。" << std::endl;
  std::cin.get();

  // 終了時にリスナーを削除する
  controller.removeListener(listener);

  return 0;
}
