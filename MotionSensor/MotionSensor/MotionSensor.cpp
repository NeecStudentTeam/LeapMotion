#include <iostream>
#include <cstring>
#include <string>
#include "Leap.h"

using namespace Leap;

class MotionListener : public Listener {
public:
	virtual void onInit(const Controller&);
	virtual void onConnect(const Controller&);
	virtual void onDisconnect(const Controller&);
	virtual void onExit(const Controller&);
	virtual void onFrame(const Controller&);
	virtual void onFocusGained(const Controller&);
	virtual void onFocusLost(const Controller&);
	virtual void onDeviceChange(const Controller&);
	
	//ジェスチャーID
	int gestureID;

private:
};
//リスナーの初期化処理　リスナーを追加した時に呼び出される
void MotionListener::onInit(const Controller& controller) {
	std::cout << "開始" << std::endl;
}

//LeapMotionセンサーと接続されたときに呼び出される
void MotionListener::onConnect(const Controller& controller) {
	std::cout << "LeapMotionと接続されました。" << std::endl;

	//ジェスチャーの有効化
	//サークル
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	//スワイプ
	controller.enableGesture(Gesture::TYPE_SWIPE);

	//誤検知率を減らす為に設定を変更　※完全に無くなるわけではない	
	controller.config().setFloat("Gesture.Circle.MinArc", 2 * PI);
	controller.config().save();
}

//LeapMotionセンサーから切断されたとき呼び出される
void MotionListener::onDisconnect(const Controller& controller) {
	std::cout << "LeapMotionと切断されました。" << std::endl;
}

//リスナーの終了処理　リスナーを削除した時に呼び出される
void MotionListener::onExit(const Controller& controller) {
	std::cout << "終了" << std::endl;
}

//フレームのデータが更新された時に呼び出される
//モーションセンサーのデータはすべてここで処理される
void MotionListener::onFrame(const Controller& controller) {

	//サークル時計周り
	bool clockwise = false;
	//サークル反時計周り
	bool counterClockwise = false;
	//スワイプ右方向
	bool rightSwipe = false;
	//スワイプ左方向
	bool leftSwipe = false;
	//スワイプ上方向
	bool upSwipe = false;
	//スワイプ下方向
	bool downSwipe = false;	

	const Frame frame = controller.frame();
	
	// ジェスチャーの取得
	const GestureList gestures = frame.gestures();
	for (int g = 0; g < gestures.count(); ++g) {
		Gesture gesture = gestures[g];

		switch (gesture.type()) {

		//サークル
		case Gesture::TYPE_CIRCLE:{
			CircleGesture circle = gesture;
			
			//ジェスチャー認識開始
			if ((gesture.state() == Leap::Gesture::State::STATE_START)){
				std::cout << "認識開始" << std::endl;
				gestureID = gesture.id();
			}
			//ジェスチャー更新中
			/*if ((gesture.state() == Leap::Gesture::State::STATE_UPDATE)){
				std::cout << "更新中" << std::endl;
			}*/
			//ジェスチャー認識完了
			if ((gesture.state() == Leap::Gesture::State::STATE_STOP)){
				//サークルの方向
				if (circle.pointable().direction().angleTo(circle.normal()) <= PI / 2) {
					clockwise = true;
				}
				else {
					counterClockwise = true;					
				}			
				//時計周り
				if (clockwise){		
					std::cout << "ID" << gesture.id() << std::endl;
					//指1本
					if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
						std::cout << "テレビを点けます!!!!!!!!" << std::endl;
					}
					//指3本
					else if (frame.fingers().extended().count() == 3 && gestureID == gesture.id()){
						std::cout << "エアコンをつけます!!!!!!!!" << std::endl;
					}
					//指5本
					else if (frame.fingers().extended().count() == 5 && gestureID == gesture.id()){
						std::cout << "照明を点けます!!!!!!!!" << std::endl;
					}
					else
					{
						std::cout << "clockwise未設定" << std::endl;
						std::cout << "," << frame.fingers().extended().count() << std::endl;
					}
				}
				//反時計周り
				if (counterClockwise){
					std::cout << "ID" << gesture.id() << std::endl;
					//指1本
					if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
						std::cout << "テレビを消します!!!!!!!!" << std::endl;
					}
					//指3本
					else if (frame.fingers().extended().count() == 3 && gestureID == gesture.id()){
						std::cout << "エアコンを消します!!!!!!!!" << std::endl;
					}
					//指5本
					else if (frame.fingers().extended().count() == 5 && gestureID == gesture.id()){
						std::cout << "照明を消します!!!!!!!!" << std::endl;
					}
					else
					{
						std::cout << "counter未設定" << std::endl;
						std::cout << "," << frame.fingers().extended().count() << std::endl;
					}
				}
			}

			break;
		}
		//スワイプ
		case Gesture::TYPE_SWIPE:{
			SwipeGesture swipe = gesture;

			//ジェスチャー認識開始
			if ((gesture.state() == Leap::Gesture::State::STATE_START)){
				std::cout << "認識開始" << std::endl;
				gestureID = gesture.id();
			}
			//ジェスチャー更新中
			/*if ((gesture.state() == Leap::Gesture::State::STATE_UPDATE)){
				std::cout << "更新中" << std::endl;
			}*/
			//ジェスチャー認識完了
			if ((gesture.state() == Leap::Gesture::State::STATE_STOP)){
				//スワイプの方向
				if (swipe.direction().x > 0.7) {
					rightSwipe = true;
				}
				else if (swipe.direction().x < -0.7){
					leftSwipe = true;
				}
				else if (swipe.direction().y > 0.7) {
					upSwipe = true;
				}
				else if (swipe.direction().y < -0.7) {
					downSwipe = true;
				}
			}

			//右方向スワイプ
			if (rightSwipe){
				//指1本
				if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
					std::cout << "ID" << gesture.id() << std::endl;
					std::cout << "チャンネルを1つ上げる!!!!!!!!" << std::endl;
				}
				else
				{
					std::cout << "right未設定" << std::endl;
					std::cout << "," << frame.fingers().extended().count() << std::endl;
				}
			}
			//左方向スワイプ
			if (leftSwipe){
				//指1本
				if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
					std::cout << "ID" << gesture.id() << std::endl;
					std::cout << "チャンネルを1つ下げる!!!!!!!!" << std::endl;
				}
				else
				{
					std::cout << "left未設定" << std::endl;
					std::cout << "," << frame.fingers().extended().count() << std::endl;
				}
			}
			//上方向スワイプ
			if (upSwipe){
				std::cout << "ID" << gesture.id() << std::endl;	
				//指1本
				if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
					std::cout << "音量を1つ上げる!!!!!!!!" << std::endl;
				}
				//指3本
				else if (frame.fingers().extended().count() == 3 && gestureID == gesture.id()){
					std::cout << "温度を1つ上げる!!!!!!!!" << std::endl;
				}
				else
				{
					std::cout << "up未設定" << std::endl;
					std::cout << "," << frame.fingers().extended().count() << std::endl;
				}
			}
			//下方向スワイプ
			if (downSwipe){
				std::cout << "ID" << gesture.id() << std::endl;
				//指1本
				if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
					std::cout << "音量を1つ下げる!!!!!!!!" << std::endl;
				}
				//指3本
				else if (frame.fingers().extended().count() == 3 && gestureID == gesture.id()){
					std::cout << "温度を1つ下げる!!!!!!!!" << std::endl;
				}
				else
				{
					std::cout << "未設定" << std::endl;
					std::cout << "," << frame.fingers().extended().count() << std::endl;
				}
			}
			break;
		}

		//認識してないジェスチャー
		default:
			std::cout << std::string(2, ' ') << "認識されてないジェスチャーです。" << std::endl;
			break;
		}
	}

	//手を認識しているとき
	/*if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
	std::cout << "認識中" << std::endl;
	}*/

}

//アプリケーションがアクティブになった時に呼び出される
void MotionListener::onFocusGained(const Controller& controller) {
	std::cout << "アプリケーションがアクティブになりました。" << std::endl;
}

//アプリケーションがアクティブでなくなった時に呼び出される
void MotionListener::onFocusLost(const Controller& controller) {
	std::cout << "アプリケーションがアクティブではなくなりました。" << std::endl;
}

//LeapMotionコントローラーの接続/切断された時に呼び出される
void MotionListener::onDeviceChange(const Controller& controller) {
	std::cout << "LeapMotionController" << std::endl;
	const DeviceList devices = controller.devices();

	for (int i = 0; i < devices.count(); ++i) {
		std::cout << "LeapMotionID: " << devices[i].toString() << std::endl;
		std::cout << "  データ配信状態: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
	}
}

//leapmotionメインプログラム
int main(int argc, char** argv) {

	// リスナーの作成
	MotionListener listener;
	Controller controller;;	

	// イベントを受けとるリスナーを登録
	controller.addListener(listener);

	//バックグラウンドモードで動作させる
	controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

	// Enterキーが押されるまで処理を続ける
	std::cout << "終了する場合はEnterを押してください" << std::endl;
	std::cin.get();

	// 終了時にリスナーを削除する
	controller.removeListener(listener);

	return 0;
}
