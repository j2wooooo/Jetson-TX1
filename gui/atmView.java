package test;

import javax.swing.JButton;
import javax.swing.JFrame;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class atmView extends JFrame implements ActionListener{
	private JButton btnStart,btnHelp;

	public atmView(String title) {
		
		/*윈도우 구성*/
		// - 윈도우 프로그램은 우측의 윈도우 종료 버튼을 누르면
		// 화면에서 사라지기는 하지만, 완전히 프로그램이 종료되지는 않음.
		// - 윈도우의 종료 버튼으로 프로그램도 함께 종료하기 위한 메소드 호출.
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(500,400);
		setTitle(title);
		
		/*버튼 구성*/
		//setLayout - 배치관리자가 없는 컨테이너 만들기
		setLayout(null);
		btnStart = new JButton("Start");
		btnHelp = new JButton("?");
		// 버튼의 적당한 가로와 세로를 알아보기
		// Dimension d = btnStart.getPreferredSize(); 
		// btnStart.setSize(d);
		btnStart.setSize(100, 30);
		btnHelp.setSize(50,30);
		//btnHelp.setBackground(Color.BLACK);
	
		btnStart.setLocation(200, 170);
		btnHelp.setLocation(430,10);
		add(btnStart);
		add(btnHelp);
		
		
		/*버튼의 이벤트 리스너 추가*/
		btnStart.addActionListener(this);
		btnHelp.addActionListener(this);
		
		setVisible(true);
	}
	
	public void actionPerformed(ActionEvent evt) {
		//클릭된 버튼의 이름을 저장
		String strCmd = evt.getActionCommand();
		
		//레이블에 클릭된 버튼의 이름을 지정
		if(strCmd.equals("Start")) {
			//btnStart.setText("버튼 눌림");
			callCommand("ipconfig");
		}else if(strCmd.equals("?")) {
			btnHelp.setText("버튼");
		}
	}
	
	// 리눅스 명령어 실행시키는 함수
	public void callCommand(String command) {
		
		Runtime rt = Runtime.getRuntime();
		
		try {
			Process p = rt.exec(command);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("자바 테스트");
		
		atmView av=new atmView("ATM GUI");
		
	
	}
}


