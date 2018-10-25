import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import java.awt.Image;
import java.awt.event.KeyListener;
import java.awt.Dimension;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Font;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.GraphicsEnvironment;
import java.awt.GraphicsDevice;
import java.io.IOException;

public class DetectingCriminal extends JFrame implements ActionListener{

	private static String user_identification; // user_identification = 1,  if hwayoung
	                         //                     = 2,  if hayoung
	private static String detection_date_time;
	private static String detection_accuracy;
	private static Dimension dimen;
	
	public DetectingCriminal() {
		
		/* full screen - in window
		this.setExtendedState( getExtendedState() | this.MAXIMIZED_BOTH);
		this.setUndecorated(true); // full screen
		setSize((int)dimen.width,(int)dimen.height); // size
		*/
		
		// full screen - in ubuntu
		GraphicsEnvironment env = GraphicsEnvironment.getLocalGraphicsEnvironment();
		GraphicsDevice device = env.getDefaultScreenDevice();
		device.setFullScreenWindow(this);
		
		
		setLayout(null);
		
		JLabel title = new JLabel("DETECTED THE CRIMINAL");
		title.setBounds(100, 50,500,100);
		title.setFont(new Font("Serif",Font.ITALIC,30));
		
		//load image
		ImageIcon criminal_img;
		ImageIcon usr_img;
		
		if(user_identification.equals(new String("1"))) {                // user - hwayoung
			criminal_img = new ImageIcon("crimial_hwa.jpg");
			usr_img = new ImageIcon("atm_user.jpg");
		}else {                                      // user - hayoung
			criminal_img = new ImageIcon("img.png");
			usr_img = new ImageIcon("img.png");
		}
		
		// resize criminal image
		Image new_criminal_img = criminal_img.getImage().getScaledInstance(320,240,java.awt.Image.SCALE_SMOOTH); // resize image
		criminal_img = new ImageIcon(new_criminal_img);
		
		JLabel criminal_ImgBox = new JLabel(criminal_img);
		criminal_ImgBox.setBounds(30,150,criminal_img.getIconWidth(),criminal_img.getIconHeight());
		
		// resize user image
		Image new_user_img = usr_img.getImage().getScaledInstance(320,240,java.awt.Image.SCALE_SMOOTH); // resize image
		usr_img = new ImageIcon(new_user_img);
		
		JLabel usr_ImgBox = new JLabel(usr_img);
		usr_ImgBox.setBounds(380,150,usr_img.getIconWidth(),usr_img.getIconHeight());
		
		JLabel label_criminal = new JLabel("HWAYOUNG");
		label_criminal.setBounds(100, 380,500,100);
		label_criminal.setFont(new Font("Serif",Font.ITALIC,20));
		
		JLabel label_user = new JLabel("ATM USER");
		label_user.setBounds(500, 380,500,100);
		label_user.setFont(new Font("Serif",Font.ITALIC,20));
		
		//JLabel label_accuracy = new JLabel("Index of Similarity : "+detection_accuracy +"% \n");	
		JLabel label_accuracy = new JLabel("Index of Similarity : 0% \n");
		label_accuracy.setBounds(180, 480,500,80);
		label_accuracy.setFont(new Font("Serif",Font.ITALIC,30));
		label_accuracy.setForeground(Color.RED);
		
		this.add(title);
		this.add(label_criminal);
		this.add(label_user);
		this.add(label_accuracy);
		this.add(criminal_ImgBox);
		this.add(usr_ImgBox);
		
		this.addKeyListener(new MyKeyListener());
		
		setVisible(true);
		
		//refresh frame
		int accuracy = Integer.parseInt(detection_accuracy);
		for(int i=0; i<=accuracy; i++) {
			label_accuracy.setText("Index of Similarity : "+i +"% \n");
			SwingUtilities.updateComponentTreeUI(this);
			try {
				Thread.sleep(30);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
	}
	
	class MyKeyListener extends KeyAdapter{
		public void keyPressed(KeyEvent e) {
			//System.out.println("pressed Key : "+e.getKeyCode());
		
			if(e.getKeyCode()==27) { // end
				System.exit(0);
			}
		}
	}
	
	
	public static void main(String[] args) {
		// 범죄자 누구인지(화영,하영) 이미지 캡쳐사진 이름, 검출 정확도
		// 예시 : 3 hwayoung 2018-10-24xxx 92
		
		// java main 에서 args 값 받아와서 인자마다 따로 전역변수 저장해두기?
		// gui 추가 - JLabel 범죄자 이름, 현재 사용자, 검출율  (+ ATM 사용시간)
		
		// TODO Auto-generated method stub
		System.out.println("자바 테스트");
		
		// get args value  ***
		user_identification = "1"; // args[0]
		detection_date_time = "2018-10-24xxxx";// args[1]
		detection_accuracy = "94"; // args[2]
		
		dimen = Toolkit.getDefaultToolkit().getScreenSize();
		
		DetectingCriminal av=new DetectingCriminal();
		
	}


	@Override
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}


