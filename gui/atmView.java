package test;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class atmView extends JFrame implements ActionListener{
	private JButton btnStart,btnHelp;
	private Label tf;

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
		tf = new Label("CashKeeper, ATM for crim prevention");
		// 버튼의 적당한 가로와 세로를 알아보기
		// Dimension d = btnStart.getPreferredSize(); 
		// btnStart.setSize(d);
		btnStart.setSize(100, 30);
		btnHelp.setSize(80,30);
		tf.setSize(300, 50);
		//btnHelp.setBackground(Color.BLACK);
	
		btnStart.setLocation(200, 170);
		btnHelp.setLocation(400,10);
		tf.setLocation(150, 100);
		add(btnStart);
		add(btnHelp);
		add(tf);
		
		
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
			callCommand("ipconfig"); // linux : ifconfig
		}else if(strCmd.equals("?")) {
			btnHelp.setText("버튼");
			
			/* 사용법 설명 pop up */
			JFrame fh = new JFrame();
			fh.setLayout(null);
			fh.setTitle("How to use Cash Keeper");
			fh.setSize(450, 350);
			
			// text
			Label h= new Label("PLEASE take off your sunglasses and mask, and show your face.");
			h.setSize(400,50);
			h.setLocation(50, 20);
			fh.add(h);
			
			// image
			//File sourceImage = new File("C:\\Users\\wwwo3\\eclipse-workspace\\test\\src\\test\\img.PNG");
			ImageIcon img = new ImageIcon("C:\\Users\\wwwo3\\eclipse-workspace\\test\\src\\test\\img.PNG");
			JLabel ImgBox = new JLabel(img);
			ImgBox.setBounds(80,80,img.getIconWidth(),img.getIconHeight());
			fh.add(ImgBox);
			
			fh.setVisible(true);
		}
	}
	
	// 리눅스 명령어 실행시키는 함수
	public void callCommand(String command) {
		
		Runtime rt = Runtime.getRuntime();
		
		try {
			Process p = rt.exec(command);
			System.out.println(p);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	
	public void howToUse() {
		System.out.println("how to use frame 들어옴");
		setTitle("How to use Cash Keeper");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(null);
		setSize(450,350);
		setVisible(true);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("자바 테스트");
		
		atmView av=new atmView("ATM GUI");
		
	
	}
}


