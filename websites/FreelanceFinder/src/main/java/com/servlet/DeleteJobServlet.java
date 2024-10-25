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

@WebServlet("/delete_job")
public class DeleteJobServlet extends HttpServlet{

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		try {
			int id= Integer.parseInt(req.getParameter("id"));

			HttpSession session = req.getSession();
			//updating jobs to db
			JobDao jobDao = new JobDao(DBConnect.getConnection());
			boolean delete = jobDao.deleteJob(id);
			if(delete) {
				System.out.println("job deleted");
				session.setAttribute("succMsg", "job deleted successfuly");
				resp.sendRedirect("view_jobs.jsp");
			} else {
				System.out.println("job not deleted");
				session.setAttribute("succMsg", "job not deleted. error coming..");
				resp.sendRedirect("view_jobs.jsp");
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
