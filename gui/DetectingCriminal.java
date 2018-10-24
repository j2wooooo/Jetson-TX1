import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class DetectingCriminal extends JFrame implements ActionListener{

	private static int user_identification; // user_identification = 1,  if hwayoung
	                         //                     = 2,  if hayoung
	
	public DetectingCriminal(int _user_identification) {
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(1300,600);
		setTitle("Detected Criminal");
		
		setLayout(null);
		
		JLabel title = new JLabel("DETECTED THE CRIMINAL");
		title.setBounds(100, 50,500,100);
		title.setFont(new Font("Serif",Font.ITALIC,30));
		
		//load image
		ImageIcon criminal_img;
		ImageIcon usr_img;
		
		if(_user_identification==1) {                // user - hwayoung
			criminal_img = new ImageIcon("criminal_hwayoung.png");
			usr_img = new ImageIcon("user_hwayoung1.jpg");
		}else {                                      // user - hayoung
			criminal_img = new ImageIcon("img.png");
			usr_img = new ImageIcon("img.png");
		}
		
		JLabel criminal_ImgBox = new JLabel(criminal_img);
		criminal_ImgBox.setBounds(0,150,criminal_img.getIconWidth(),criminal_img.getIconHeight());
		
		JLabel usr_ImgBox = new JLabel(usr_img);
		usr_ImgBox.setBounds(500,150,usr_img.getIconWidth(),usr_img.getIconHeight());
		
		this.add(title);
		this.add(criminal_ImgBox);
		this.add(usr_ImgBox);
		
		setVisible(true);
	}
	
	
	public static void main(String[] args) {
		// 범죄자 누구인지(화영,하영) 이미지 캡쳐사진 이름, 검출 정확도
		// 예시 : 3 hwayoung 2018-10-24xxx 92
		
		// java main 에서 args 값 받아와서 인자마다 따로 전역변수 저장해두기?
		// gui 추가 - JLabel 범죄자 이름, 현재 사용자, 검출율  (+ ATM 사용시간)
		
		// TODO Auto-generated method stub
		System.out.println("자바 테스트");
		
		// get args value  ***
		user_identification = 1;
		
		DetectingCriminal av=new DetectingCriminal(user_identification);
		
	}


	@Override
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}


