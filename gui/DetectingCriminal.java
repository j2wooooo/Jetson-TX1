import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class DetectingCriminal extends JFrame implements ActionListener{

	public DetectingCriminal() {
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(1300,600);
		setTitle("Detected Criminal");
		
		// image
		ImageIcon criminal_img = new ImageIcon("img.png");
		JLabel criminal_ImgBox = new JLabel(criminal_img);
		criminal_ImgBox.setBounds(0,150,criminal_img.getIconWidth(),criminal_img.getIconHeight());
		criminal_ImgBox.setLocation(50, 100);
		
		ImageIcon usr_img = new ImageIcon("img.png");
		JLabel usr_ImgBox = new JLabel(usr_img);
		usr_ImgBox.setBounds(0,150,usr_img.getIconWidth(),usr_img.getIconHeight());
		usr_ImgBox.setLocation(50, 100);
		
		this.add(criminal_ImgBox);
		this.add(usr_ImgBox);
		
		setVisible(true);
	}
	
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("자바 테스트");
		
		DetectingCriminal av=new DetectingCriminal();
		
	
	}


	@Override
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}


