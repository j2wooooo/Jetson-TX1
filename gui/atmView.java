import java.util.Scanner;
import java.lang.Runtime;
import java.lang.Exception;
import java.io.BufferedReader;
import java.io.InputStreamReader;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.*;
import java.awt.*;
import java.io.IOException;
import java.awt.BorderLayout;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.*;


public class atmView extends JFrame{
	
	private JPanel panel = new JPanel();
	private JButton btnStart,btnHelp;
	private JLabel tf;
	public JFrame cp;
	public JFrame fh;
	public int flag = 0;

	public atmView(String title) {

		/*윈도우 구성*/
		// - 윈도우 프로그램은 우측의 윈도우 종료 버튼을 누르면
		// 화면에서 사라지기는 하지만, 완전히 프로그램이 종료되지는 않음.
		// - 윈도우의 종료 버튼으로 프로그램도 함께 종료하기 위한 메소드 호출.
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//===============add===============
		// frame size
		setSize(1850,1000);
		// panel size, title
		panel.setLayout(null);
		panel.setSize(1850,1000);
		setTitle(title);
		//===============end===============

		/*버튼 구성*/
		//setLayout - 배치관리자가 없는 컨테이너 만들기
		//setLayout(null);
		//setLayout(new BorderLayout());
		btnStart = new JButton("Start");
		btnHelp = new JButton("?");
		tf = new JLabel("CashKeeper, ATM for crime prevention");
		// 버튼의 적당한 가로와 세로를 알아보기
		// Dimension d = btnStart.getPreferredSize(); 
		// btnStart.setSize(d);
		//tf.setSize(300, 50);
		//btnHelp.setBackground(Color.BLACK);
	
		//===================add===================
		// buttons, lable : location(x,y), size(x,y)
		btnStart.setBounds(805, 550,240,90);
		btnStart.setFont(new Font("Serif",Font.ITALIC,30));
		btnHelp.setBounds(1740,10,100,100);
		btnHelp.setFont(new Font("Serif",Font.ITALIC,30));
		tf.setBounds(420, 450,1200,100);
		tf.setFont(new Font("Serif",Font.ITALIC,50));
		
		// buttons, label, keylistener : attach to panel
		panel.add(btnStart);
		panel.add(btnHelp);
		panel.add(tf);
		
		// panel add to frame
		panel.addKeyListener(new MyKeyListener());
		add(panel);
		
		
		setVisible(true);
		panel.setFocusable(true);
		panel.requestFocus();
	}
	// keyboard listener
	class MyKeyListener extends KeyAdapter
	{
		
		public void keyPressed(KeyEvent e)
		{
			JFrame cp = new JFrame();
			
			System.out.println("pressed key : "+e.getKeyCode());
			System.out.println("flag : "+flag);
			if(e.getKeyCode() == '\n')
			{
				//callCommand("ifconfig"); // linux : ifconfig
				//callCommand("ls"); // linux : ifconfig
				System.exit(0);
			}
			else{
				
				
				if(e.getKeyCode() == 27 && flag == 1)
				{
					System.out.println("pressed esc\n");
					fh.dispose();
					flag = 0;
				}
				else{
					
					/* 사용법 설명 pop up */
					fh = new JFrame();
					fh.setLayout(null);
					fh.setTitle("How to use Cash Keeper");
					fh.setSize(1850, 1000);
			
					// text
					JLabel h= new JLabel("PLEASE take off your sunglasses and mask, and show your face.");
					
					h.setBounds(380,0,1500,250);
					h.setFont(new Font("Serif",Font.ITALIC,30));
					fh.add(h);
			
					// image
					ImageIcon img = new ImageIcon("img.png");
					JLabel ImgBox = new JLabel(img);
					ImgBox.setBounds(400,150,img.getIconWidth(),img.getIconHeight());
					fh.add(ImgBox);
					fh.addKeyListener(new MyKeyListener());
			
					fh.setVisible(true);
					//FrameQuestion.createAndShowGUI();
					flag = 1;
					
				}
			}
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
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//System.setProperty("java.awt.headless","true");
		String temp = System.getProperty("java.awt.headless");
		
		System.out.println("java test "+temp);
		atmView av=new atmView("ATM GUI");
		
	
	}
}
