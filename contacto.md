---
layout: default
title: Contacto
---

## 📩 Contáctanos

<form action="https://formspree.io/f/xdkglzar" method="POST">
    <!-- Campo "honeypot" anti-spam (oculto) -->
    <input type="text" name="_gotcha" style="display:none">
    <!-- Redirección tras enviar -->
    <input type="hidden" name="_next" value="{{ site.url }}/gracias" >
    <!-- Campos visibles del formulario -->
    <div>
        <label for="name">Nombre:</label>
        <input type="text" id="name" name="name" required>
    </div>
    <div>
        <label for="email">Email:</label>
        <input type="email" id="email" name="_replyto" required>
    </div>
    <div>
        <label for="message">Mensaje:</label>
        <textarea id="message" name="message" rows="4" required></textarea>
        <button type="submit" class="btn">Enviar</button>
    </div>
</form>