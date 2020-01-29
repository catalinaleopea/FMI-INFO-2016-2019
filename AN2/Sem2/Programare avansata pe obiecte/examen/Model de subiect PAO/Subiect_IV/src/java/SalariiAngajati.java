import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(urlPatterns =
{
    "/SalariiAngajati"
})
public class SalariiAngajati extends HttpServlet
{
    Connection conn = null;
    @Override
    public void init() throws ServletException
    {
        //super.init(); 
        try
        {
            conn = DriverManager.getConnection("jdbc:derby://localhost:1527/AngajatiFirma", "root", "12345");
        } catch (SQLException ex)
        {
        }
    }

    @Override
    public void destroy()
    {
        //super.destroy(); //To change body of generated methods, choose Tools | Templates.
        if(conn != null)
            try {
                conn.close();
            } catch (SQLException ex) {
            
            }
    }
    
    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
       
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        //processRequest(request, response);
        try (PrintWriter out = response.getWriter())
        {
            /* TODO output your page here. You may use following sample code. */
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<body>");
            
            float min = Float.parseFloat(request.getParameter("min"));
            
            PreparedStatement pst = null;
            ResultSet rs = null;
            
            try
            {
                pst = conn.prepareStatement("SELECT * FROM DATEANGAJATI WHERE Salariu > ?");
                pst.setFloat(1 , min);
                
                rs = pst.executeQuery();
                
                while(rs.next())
                    out.println("<h1>" + rs.getString("Nume") + " " + rs.getFloat("Salariu") + " " + rs.getInt("Varsta"));
                
            } catch (SQLException ex)
            {
                
            }
            finally
            {
                
                try {
                    if(rs != null)    
                        rs.close();
                    if(pst != null)
                        pst.close();
                } catch (SQLException ex) {
                    
                }
                
            }

            out.println("</body>");
            out.println("</html>");
        }
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo()
    {
        return "Short description";
    }// </editor-fold>

}
