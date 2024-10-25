package com.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.DB.DBConnect;
import com.dao.JobDao;
import com.entity.Jobs;

@WebServlet("/add_job")
public class AddPostServlet extends HttpServlet{

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {

		try {
			String title = req.getParameter("title");
			String description = req.getParameter("description");
			String category = req.getParameter("category");
			String status = req.getParameter("status");
			String location = req.getParameter("location");

			Jobs jobs = new Jobs();
			jobs.setTitle(title);
			jobs.setDescription(description);
			jobs.setCategory(category);
			jobs.setStatus(status);
			jobs.setLocation(location);

			HttpSession session = req.getSession();

			//saving jobs to db
			JobDao jobDao = new JobDao(DBConnect.getConnection());
			boolean add = jobDao.addJob(jobs);
			if(add) {
				System.out.println("job added");
				session.setAttribute("succMsg", "job posting done successfuly");
				resp.sendRedirect("add_job.jsp");
			} else {
				System.out.println("job not added");
				session.setAttribute("succMsg", "job posting not done. error coming..");
				resp.sendRedirect("add_job.jsp");
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}



}
